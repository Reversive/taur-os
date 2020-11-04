#ifndef _CONSOLE_H
#define _CONSOLE_H

#define ESC_ASCII 27
#define MAX 255

#include "time.h"
#include "inforeg.h"
#include "print_mem.h"
unsigned int command_equal(char * str1, char * str2);
void assign_module(char * str);
unsigned int console_finish_handler();
unsigned int is_newline_char(char chr);
void console_key_handler(char input);
void help();

#endif