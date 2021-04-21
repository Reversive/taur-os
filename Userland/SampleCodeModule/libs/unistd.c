#include "../include/unistd.h"


pid_t execv(char *name, function f, char **argv) {
    return sys_create_process(name, f, argv);
}