#ifndef PIPES_H_
#define PIPES_H_
#include "../dispatcher/include/scheduler.h"
#include <stdint.h>
#include "../task/include/process.h"
#include "lib.h"
#include "../sync/include/sem.h"

int pipe_write(int index, char *addr, int n);
int pipe_read(int index, char *addr, int n);
int pipe_open(char* name);
void pipe_close(int index);
char* pipes_info();
#endif