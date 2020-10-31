#ifndef _SYSCALLS_H
#define _SYSCALLS_H
#include <stdint.h>
#include "../../drivers/keyboard/include/kb_driver.h"
#include "../../drivers/shell/include/shell.h"
#define _STDIN 0x1
typedef uint64_t syscall(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8);
typedef unsigned int size_t;

enum file_descriptors {
    _FD_STD_OUT = 0,
    _FD_STD_IN  = 1,
    _FD_STD_ERR = 2
};

enum syscall_numbers {
    _SYSCALL_READ = 0,
	_SYSCALL_WRITE,
    _SYSCALL_TIME
};

#define _SYSCALLS_LAST _SYSCALL_TIME
#define _SYSCALLS_SIZE (_SYSCALLS_LAST + 1)

syscall syscall_read;
syscall syscall_write;
syscall syscall_time;


extern syscall * syscalls_table[_SYSCALLS_SIZE];

int read(unsigned int fd, char * buffer, size_t count);
int write(unsigned int fd, char * buffer, size_t count);

#endif