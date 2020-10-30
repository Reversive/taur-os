#ifndef _BASIC_LIB_H
#define _BASIC_LIB_H
#include <stdint.h>
typedef unsigned int size_t;
#define STDIN 0x1
uint64_t _syscall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8);
unsigned int sys_time(char setting);
size_t sys_read(char * buffer, size_t length);

#endif