#ifndef _SYSCALL_H
#define _SYSCALL_H
#include <stdint.h>
#include "syscalls.h"
#include "../../drivers/shell/include/shell.h"
#define SUCCESS 1
uint64_t sys80handler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8);
extern unsigned int get_time(char t);

#endif