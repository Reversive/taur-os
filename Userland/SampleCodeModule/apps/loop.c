// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/loop.h"


void print_message() {
    printfd("[PROCESS %d] Este es un mensaje desde loop!\n", getpid());
}

int loop(int argc, char **argv) {
    sys_register_timertick_function(print_message, TICK_SECOND * SECONDS, getpid());
    while(1);
    sys_sem_post("pipe");
}

