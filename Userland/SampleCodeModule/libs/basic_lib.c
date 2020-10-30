#include "../include/basic_lib.h"

unsigned int sys_time(char format) {
    return (unsigned int) _syscall(0x2, format, 0, 0, 0);
}

size_t sys_read(char * buffer, size_t length) {
    return (size_t) _syscall(0x0, STDIN, (uint64_t) buffer, length, 0);
}