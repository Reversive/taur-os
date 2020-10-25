#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <naiveConsole.h>
#include <interrupts.h>
typedef unsigned char bool;
#define PIC_MASK 0xFF

typedef struct s_register {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rdi;
    uint64_t rsi;
    char padding[8];
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
} registers;

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
void dump_reg(uint64_t * rip, uint64_t * rsp);
void kernel_panic(uint64_t * rip, uint64_t * rsp, int id, const char * desc, bool halt);
char *cpuVendor(char *result);
void clear_interrupts();
void halt_system();
void invalidOpcodeTest(void);

#endif