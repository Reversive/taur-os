// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/pipe.h"

pipe_t pipes[MAXPIPES];

void blockProcessPipe(int * p, int pid);
void releaseProcessesPipe(int * p);

int pipeWrite(int index, char *addr, int n) {
    // bloqueo proceso
    semWait(pipes[index].name);
    // desbloqueo el proceso
    int i;
    for (i = 0; i < n && addr[i] != 0; i++) {
        pipes[index].data[pipes[index].nwrite++ % PIPESIZE] = addr[i];
    }
    pipes[index].data[pipes[index].nwrite % PIPESIZE] = -1;
    
    semPost(pipes[index].name);
    return i;
}

// process -->el que esta usando
// bloq --->  

int pipeRead(int index, char *addr, int n) {
    //if(pipes[index].isusing != NULL){
        // me bloqueo
    //}
    
    // bloqueo proceso
    semWait(pipes[index].name);
    //desbloqueo proceso
    //_internal_print_string("after wait\n");
    
    int i ;
    for (i = 0; i < n && pipes[index].data[pipes[index].nread % PIPESIZE] != -1; i++) {
        addr[i] = pipes[index].data[pipes[index].nread++ % PIPESIZE];
    }
    semPost(pipes[index].name);
    /*if(pipes[index].bloqProcesses!= NULL){
        pipes[index].wProcesses
    }*/
    addr[i] = 0;
    if (pipes[index].data[pipes[index].nread % PIPESIZE] == -1)
        pipes[index].data[pipes[index].nread % PIPESIZE] = 0;
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
        if (my_strcmp(name, pipes[i].name) == 0)
        {
            return i;
        }
    }
    
    return -1;
}

int pipeOpen(char* name) {
    //_internal_print_string("pipe open\n");
    int i;
    if((i = lookPipe(name)) != -1){
        // pipe already opened
        //_internal_print_string("pipe already open");
        //_internal_print_dec(i);
        //_internal_print_string("\n");
        return pipes[i].fd;
    }
    int firstFree = nextPipe();
    if (firstFree == -1)
        return -1;
    pipes[firstFree].fd = firstFree+2;
    pipes[firstFree].created = 1;
    pipes[firstFree].usingPipe = 0;
    pipes[firstFree].waitingPid = -1;
    semOpen(name, 1);
    my_strcpy(pipes[firstFree].name, name);
    //_internal_print_string("new pipe");
    //_internal_print_dec(firstFree);
    //_internal_print_string("\n");
    return pipes[firstFree].fd; //devuelvo el file descriptor de mi pipe que sera el que use mi proceso para acceder al buffer
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

void fill0(char* arr){
    int i =0;
    while(arr[i]!= 0){
        arr[i] = 0;
    }
}

char retpipes[MAXPIPES*100] = {0};

char *pipesInfo() {
    _internal_print_string("in pipe Info\n");
    fill0(retpipes);
    int cant = 0;
    char namePipe[10], brp[50] = {0}, bwp[50] = {0};
    for (int p=0; p < MAXPIPES; p++) {
        if (pipes[p].created != 0) {
            cant++;
            //itoa(p, namePipe, 10);
            my_strcpy(namePipe, pipes[p].name);
            listBlockedProcesses(pipes[p].rProcesses, brp);
            listBlockedProcesses(pipes[p].wProcesses, bwp);
            my_strcat(retpipes, "Pipe: ");
            my_strcat(retpipes, namePipe);
            my_strcat(retpipes, "\n");
            my_strcat(retpipes, "State: ");
            my_strcat(retpipes, pipes[p].data + (pipes[p].nread % PIPESIZE));
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

void blockProcessPipe(int * p, int pid) {
    int i;
    for(i = 0; i < PROCESSES && p[i] != 0; i++);
    if (i == PROCESSES)
        return;
    p[i] = pid;
    //_internal_print_string("process blocked");
    //_internal_print_dec(pid);
    //_internal_print_string("\n");
    set_process_state(pid, BLOCKED);
}

void releaseProcessesPipe(int * p) {
    for (int i=0; i < PROCESSES && p[i] != 0;  i++) {
        //_internal_print_string("process ready");
        //_internal_print_dec(p[i]);
        //_internal_print_string("\n");
        set_process_state(p[i], READY);
        p[i] = 0;
    }
}
