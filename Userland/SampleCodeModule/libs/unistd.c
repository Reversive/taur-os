#include "../include/unistd.h"


pid_t execv(char *name, main_function f, char **argv) {
    return sys_create_process(name, f, argv);
}

pid_t getpid() {
    return sys_getpid();
}

pid_t kill(pid_t pid) {
    return sys_kill_process(pid);
}

pid_t nice(pid_t pid, int priority) {
    return sys_set_niceness(pid, priority);
}

pid_t block(pid_t pid) {
    return sys_block(pid);
}