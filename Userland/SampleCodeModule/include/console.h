#ifndef _CONSOLE_H
#define _CONSOLE_H

#define ESC_ASCII 27
#define MAX 255
#define MAX_ARGS 10
#define INVALID_PID -1
#include "time.h"
#include "inforeg.h"
#include "print_mem.h"
#include "basic_lib.h"
#include "../apps/include/test_mm.h"
#include "../apps/include/test_processes.h"
#include "unistd.h"
#include "../apps/include/loop.h"

#define PROGRAM_COUNT 2
typedef char *parameters[MAX_ARGS];

unsigned int command_equal(char * str1, char * str2);
void assign_module(char * str);
unsigned int console_finish_handler(char* input_buffer);
unsigned int is_newline_char(char chr);
void console_key_handler(char input, char* input_buffer);
void help();
#endif