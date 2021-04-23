#include "include/loop.h"


void print_message() {
    printf("[PROCESS %d] Este es un mensaje desde loop!\n", getpid());
}

int loop(int argc, char **argv) {
    sys_register_timertick_function(print_message, TICK_SECOND * SECONDS, getpid());
    while(1);
}

