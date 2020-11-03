#ifndef _STDIO_H
#define _STDIO_H
#include "basic_lib.h"
#define SIZE_BYTE 8
#define EOF -1
enum file_descriptors {
    _FD_STD_OUT = 0,
    _FD_STD_IN  = 1,
    _FD_STD_ERR = 2
};

unsigned int getchar(void);
unsigned int putchar(char c);
int puts(const char *str);
unsigned int strlen(char * str);
void printString(char * str);
void PrintInfoReg( char *data);
char getcharData( char hexaNum);
unsigned int commandEql(char * str1, char * str2);
void asignarModulo(char * str);
unsigned int consoleFinishHandler();
unsigned int finishChar(char chr);
void consoleKeyHandler(char input);
void help();

#endif