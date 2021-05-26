#ifndef _STDIO_H
#define _STDIO_H
#include "basic_lib.h"
#include "../include/inforeg.h"
#include <stdarg.h>
#include "math.h"
#define SIZE_BYTE 8
#define EOF -1
enum file_descriptors {
    _FD_STD_OUT = 0,
    _FD_STD_IN  = 1,
    _FD_STD_ERR = 2
};

extern int fd_pipe[2];

unsigned int getchar(void);
unsigned int putchar(char c);
int puts(const char *str);
unsigned int strlen(char * str);
void print_string(char * str);
char *itoa(uint64_t value, char *buffer, uint32_t base);
int atoi(char* str);
int printfd(char *fmt, ...);
int printf(char * fmt, ...);
int scanf(char* source, char* format, ...);
void hex_to_string(long num, char * buffer);
char * strcpy(char* destination, const char* source);
char * strchr (register const char *s, int c);
char* strcat(char* destination, const char* source);


#endif