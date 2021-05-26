// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/loop.h"
#include "include/test_prio.h"
int loop(int argc, char **argv) {
    
    while(1) {
        bussy_wait(MEDIUM_WAIT);
        printf(" %d ", sys_getpid());
    }
    sys_sem_post("pipe");
    return 0;
}

