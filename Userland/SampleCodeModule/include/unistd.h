#ifndef UNISTD_H
#define UNISTD_H
#include "basic_lib.h"
pid_t execv(char *name, main_function f, char **argv, int foreground);
pid_t getpid();
pid_t kill(pid_t pid);
pid_t nice(pid_t pid, int priority);
pid_t block(pid_t pid);
#endif