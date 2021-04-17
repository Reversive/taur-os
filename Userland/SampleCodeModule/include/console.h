#ifndef _CONSOLE_H
#define _CONSOLE_H

#define ESC_ASCII 27
#define MAX_DATA_BUFFER 256
#define MAX 255

#include "time.h"
#include "inforeg.h"
#include "print_mem.h"
#include "basic_lib.h"

unsigned int command_equal(char * str1, char * str2);
void assign_module(char * str);
unsigned int console_finish_handler(char* buffer);
unsigned int is_newline_char(char chr);
void console_key_handler(char input,char* buffer);
void help();
void print_string_by_pos(int x, int y, char * str, int color, int size);
#endif