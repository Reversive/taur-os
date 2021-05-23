#ifndef PIPES_H_
#define PIPES_H_
#include "../dispatcher/include/scheduler.h"
#include <stdint.h>

/*#define MAXPIPES 10
#define PIPESIZE 1000
#define PROCESSES 10

typedef struct {
    int created;
    char data[PIPESIZE];
    int rProcesses[PROCESSES];
    int wProcesses[PROCESSES];
    unsigned int nread;
    unsigned int nwrite;
}pipe_t;
*/

int pipeWrite(int index, char *addr, int n);
int pipeRead(int index, char *addr, int n);
int pipeOpen(char* name, int fd[2]);
void pipeClose(int index);
char* pipesInfo();
#endif