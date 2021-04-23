#include "../include/unistd.h"


pid_t execv(char *name, main_function f, char **argv) {
    return sys_create_process(name, f, argv);
}

pid_t getpid() {
    return sys_getpid();
}

void kill(pid_t pid) {
    sys_kill_process(pid);
}