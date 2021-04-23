#ifndef UNISTD_H
#define UNISTD_H
#include "basic_lib.h"
pid_t execv(char *name, main_function f, char **argv);

#endif