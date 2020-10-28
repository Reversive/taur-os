#include "include/sys_handler.h"

int sys80handler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {

    if(rdi > SYSCALL_QTY) return -1;
    switch (rdi)
    {
    case GET_TIME:
        return get_time(rsi);
        break;
    
    default:
        return -1;
        break;
    }

}
