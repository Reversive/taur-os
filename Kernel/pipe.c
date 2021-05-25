// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/pipe.h"

pipe_t pipes[MAXPIPES];

void block_process_pipe(int * p, int pid);
void release_process_pipe(int * p, int pid);

int pipe_write(int index, char *addr, int n) {

    block_process_pipe(pipes[index].wProcesses, get_current_pid());
    sem_wait(pipes[index].name);
    release_process_pipe(pipes[index].wProcesses, get_current_pid());
    int i;
    for (i = 0; i < n && addr[i] != 0; i++) {
        pipes[index].data[pipes[index].nwrite++ % PIPESIZE] = addr[i];
    }
    pipes[index].data[pipes[index].nwrite % PIPESIZE] = -1;
    
    sem_post(pipes[index].name);
    return i;
}


int pipe_read(int index, char *addr, int n) {
    
    block_process_pipe(pipes[index].rProcesses, get_current_pid());
    sem_wait(pipes[index].name);
    release_process_pipe(pipes[index].wProcesses, get_current_pid());
    
    
    int i ;
    for (i = 0; i < n && pipes[index].data[pipes[index].nread % PIPESIZE] != -1; i++) {
        addr[i] = pipes[index].data[pipes[index].nread++ % PIPESIZE];
    }
    sem_post(pipes[index].name);
    /*if(pipes[index].bloqProcesses!= NULL){
        pipes[index].wProcesses
    }*/
    addr[i] = 0;
    if (pipes[index].data[pipes[index].nread % PIPESIZE] == -1)
        pipes[index].data[pipes[index].nread % PIPESIZE] = 0;
    return i;
}

int next_pipe() {
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

int look_pipe(char* name) {

    for (int i = 0; i < MAXPIPES ; i++)
    {
        if (my_strcmp(name, pipes[i].name) == 0)
        {
            return i;
        }
    }
    
    return -1;
}

int pipe_open(char* name) {
    //_internal_print_string("pipe open\n");
    int i;
    if((i = look_pipe(name)) != -1){
        // pipe already opened
        //_internal_print_string("pipe already open");
        //_internal_print_dec(i);
        //_internal_print_string("\n");
        return pipes[i].fd;
    }
    int first_free = next_pipe();
    if (first_free == -1)
        return -1;
    pipes[first_free].fd = first_free+2;
    pipes[first_free].created = 1;
    pipes[first_free].usingPipe = 0;
    pipes[first_free].waitingPid = -1;
    sem_open(name, 1);
    my_strcpy(pipes[first_free].name, name);
    //_internal_print_string("new pipe");
    //_internal_print_dec(first_free);
    //_internal_print_string("\n");
    return pipes[first_free].fd; //devuelvo el file descriptor de mi pipe que sera el que use mi proceso para acceder al buffer
}

void pipe_close(int index) {
    for (int i=0; i < PROCESSES;  i++) {
        pipes[index].rProcesses[i] = 0;
        pipes[index].wProcesses[i] = 0;
    }
    pipes[index].data[0] = 0;
    pipes[index].nread = 0;
    pipes[index].nwrite = 0;
    pipes[index].created = 0;
}

void list_blocked_processes(int * p, char * buf) {
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

char *pipes_info() {
    fill0(retpipes);
    int cant = 0;
    char namePipe[10], brp[50] = {0}, bwp[50] = {0};
    for (int p=0; p < MAXPIPES; p++) {
        if (pipes[p].created != 0) {
            cant++;
            //itoa(p, namePipe, 10);
            my_strcpy(namePipe, pipes[p].name);
            list_blocked_processes(pipes[p].rProcesses, brp);
            list_blocked_processes(pipes[p].wProcesses, bwp);
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

void block_process_pipe(int * p, int pid) {
    int i;
    for(i = 0; i < PROCESSES && p[i] != 0; i++){
        if(p[i] == pid){
            set_process_state(pid, BLOCKED);
            return;
        }
    }
    if (i == PROCESSES)
        return;
    p[i] = pid;
    set_process_state(pid, BLOCKED);
}

void release_process_pipe(int * p, int pid) {
    for (int i=0; i < PROCESSES ;  i++) {
        if(p[i] == pid){
            set_process_state(p[i], READY);
            p[i] = 0;
            return;
        }
    }
}
