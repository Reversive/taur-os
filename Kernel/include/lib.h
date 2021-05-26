#ifndef LIB_H
#define LIB_H

    #include "../cpu/include/defs.h"
    #include <stdint.h>

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

    void * memset(void * destination, int32_t c, uint64_t length);
    void * memcpy(void * destination, const void * source, uint64_t length);
    void dump_reg(int id, const char * desc, uint64_t * rip, uint64_t * rsp, uint64_t * top);
    char *cpuVendor(char *result);
    void halt_system();
    int strnlen(char * str);
    void my_strcpy(char * dest, char * origin);
    void get_registers(unsigned char *data);
    int strcomp(char * str1, char * str2);
    char* my_strcat(char* destination, const char* source);
    char *itoa(uint64_t value, char *buffer, uint32_t base);
    extern void save_registers_data(unsigned char* data);
    void print_reg();
    extern int test();
    char get_char_data( char hexa_num);

#endif