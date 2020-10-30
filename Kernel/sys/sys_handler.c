#include "include/sys_handler.h"


syscall * syscalls_table[_SYSCALLS_SIZE] = {
	[_SYSCALL_READ] = syscall_read,
	[_SYSCALL_WRITE] = syscall_write,
    [_SYSCALL_TIME] = syscall_time
};


uint64_t sys80handler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    if( rdi < 0 || rdi > _SYSCALLS_SIZE) return -1;
    return syscalls_table[rdi](rsi, rdx, rcx, r8);
}

uint64_t syscall_read(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    unsigned int fd = (unsigned int) rsi;
    char * buffer = (char *) rdx;
    size_t count = (size_t) rcx;
    return read(fd, buffer, count);
}

uint64_t syscall_write(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    return -1; //TODO
}

uint64_t syscall_time(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    char setting = (char) rsi;
    return get_time(setting);
}