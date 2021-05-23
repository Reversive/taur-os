// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/pipe.h"

pipe_t pipes[MAXPIPES];


void blockProcessPipe(int * p, int pid) {
    int i;
    for(i = 0; i < PROCESSES && p[i] != 0; i++);
    if (i == PROCESSES)
        return;
    p[i] = pid;
    set_process_state(pid, BLOCKED);
}

void releaseProcessesPipe(int * p) {
    for (int i=0; i < PROCESSES && p[i] != 0;  i++) {
        set_process_state(p[i], READY);
        p[i] = 0;
    }
}

int pipeWrite(int index, char *addr, int n) {
    int i;
    for (i = 0; i < n && addr[i] != 0; i++) {
        while (pipes[index].nwrite >= pipes[index].nread + PIPESIZE)
            blockProcessPipe(pipes[index].wProcesses, get_current_pid());
        pipes[index].data[pipes[index].nwrite++ % PIPESIZE] = addr[i];
    }
    pipes[index].data[pipes[index].nwrite % PIPESIZE] = -1;
    releaseProcessesPipe(pipes[index].wProcesses);
    return i;
}

int pipeRead(int index, char *addr, int n) {
    int i;
    for (i = 0; i < n && pipes[index].data[pipes[index].nread % PIPESIZE] != -1; i++) {
        while (pipes[index].nread >= pipes[index].nwrite) {
            blockProcessPipe(pipes[index].rProcesses, get_current_pid());
        }
        addr[i] = pipes[index].data[pipes[index].nread++ % PIPESIZE];
    }
    addr[i] = 0;
    if (pipes[index].data[pipes[index].nread % PIPESIZE] == -1)
        pipes[index].data[pipes[index].nread % PIPESIZE] = 0;
    releaseProcessesPipe(pipes[index].rProcesses);
    return i;
}

int nextPipe() {
    int aux = 0;
    while (aux < MAXPIPES && pipes[aux].created != 0)
        aux++;
    return (aux == MAXPIPES) ? -1 : aux;
}
int my_strcmp(const char *X, const char *Y)
{
    while (*X)
    {
        // if characters differ, or end of the second string is reached
        if (*X != *Y) {
            break;
        }
 
        // move to the next pair of characters
        X++;
        Y++;
    }
 
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}
int lookPipe(char* name) {
    for (int i = 0; i < MAXPIPES ; i++)
    {
        if (my_strcmp(name, pipes[i].name))
        {
            return i;
        }
    }
    
    return -1;
}
int pipeOpen(char* name, int fd[2]) {
    int i;
    if((i = lookPipe(name)) != -1){
        // pipe already opened
        fd[0] = (i+1)*10;
        fd[1] = fd[0] + 1;
        return i;
    }
    int aux = nextPipe();
    if (aux == -1)
        return -1;
    fd[0] = (aux+1)*10;
    fd[1] = fd[0] + 1;
    pipes[aux].created = 1;
    my_strcpy(pipes[aux].name, name);
    return aux;
}

void pipeClose(int index) {
    for (int i=0; i < PROCESSES;  i++) {
        pipes[index].rProcesses[i] = 0;
        pipes[index].wProcesses[i] = 0;
    }
    pipes[index].data[0] = 0;
    pipes[index].nread = 0;
    pipes[index].nwrite = 0;
    pipes[index].created = 0;
}

pipe_t * getPipe(int p) {
    int aux = p/10 - 1;
    return &pipes[aux];
}

void listBlockedProcesses(int * p, char * buf) {
    char pid[5]={0};
    for (int i = 0; i < PROCESSES; i++) {
        if (p[i] != 0) {
            itoa(p[i], pid, 10);
            my_strcat(buf, pid);
            my_strcat(buf, ", ");
        }
    }
}

char retpipes[MAXPIPES*100] = {0};
char *pipesInfo() {
    int cant = 0;
    char namePipe[10], brp[50] = {0}, bwp[50] = {0};
    for (int p=0; p < MAXPIPES; p++) {
        if (pipes[p].created != 0) {
            cant++;
            itoa(p, namePipe, 10);
            my_strcat(namePipe, pipes[p].name);
            listBlockedProcesses(pipes[p].rProcesses, brp);
            listBlockedProcesses(pipes[p].wProcesses, bwp);
            my_strcpy(retpipes, "Pipe: ");
            my_strcat(retpipes, namePipe);
            my_strcat(retpipes, "\n");
            my_strcat(retpipes, "State: ");
            my_strcat(retpipes, pipes[p].data);
            my_strcat(retpipes, "\n");
            my_strcat(retpipes, "Blocked Read Processes: ");
            my_strcat(retpipes, brp);
            my_strcat(retpipes, "\n");
            my_strcat(retpipes, "Blocked Write Processes: ");
            my_strcat(retpipes, bwp);
            my_strcat(retpipes, "\n");
        }
    }
    if (cant == 0)
        my_strcpy(retpipes, "No pipes available\n");
    return retpipes;
}
