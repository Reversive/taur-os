#include "../include/unistd.h"


pid_t execv(char *name, main_function f, char **argv) {
    return sys_create_process(name, f, argv);
}