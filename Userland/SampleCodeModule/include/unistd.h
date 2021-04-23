#ifndef UNISTD_H
#define UNISTD_H
#include "basic_lib.h"
pid_t execv(char *name, main_function f, char **argv);
pid_t getpid();
void kill(pid_t pid);
#endif