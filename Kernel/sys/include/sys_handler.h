#ifndef _SYSCALL_H
#define _SYSCALL_H
#include <stdint.h>
#include "../../include/naiveConsole.h"
#define SYSCALL_QTY 12
#define GET_TIME 0
int sys80handler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8);
extern unsigned int get_time(char t);
#endif