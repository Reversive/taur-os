#ifndef _STDIO_H
#define _STDIO_H
#include "basic_lib.h"
#define EOF -1
enum file_descriptors {
    _FD_STD_OUT = 0,
    _FD_STD_IN  = 1,
    _FD_STD_ERR = 2
};

unsigned int getchar(void);
unsigned int putchar(char c);
int puts(const char *str);
#endif