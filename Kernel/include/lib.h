#ifndef LIB_H
#define LIB_H

#include <naiveConsole.h>
#include "../cpu/include/defs.h"
#include "../asm/include/interrupts.h"


typedef unsigned char bool;
#define PIC_MASK 0xFF


typedef struct fs_register {
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
} full_reg_snapshot;

typedef struct ss_register {
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t r8;
    uint64_t r9;
} sys_reg_snapshot;

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
void dump_reg(int id, const char * desc, uint64_t * rip, uint64_t * rsp, uint64_t * top);
void kernel_panic(uint64_t * rip, uint64_t * rsp, uint64_t * top, int id, const char * desc, bool halt);
char *cpuVendor(char *result);
void clear_interrupts();
void halt_system();

void get_registers(char *data);

char getcharData(char hexaNum);
extern void save_registers_data(char* data);
void print_reg();
extern int test();

#endif