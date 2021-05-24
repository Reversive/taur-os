#ifndef _PRINT_MEM_H
#define _PRINT_MEM_H
#include "basic_lib.h"
#include "stdio.h"

void print_mem(char * from, char * buffer);
int info_mem( char * str);
int is_hexa_digit(char digit);
char * parse_str_to_hexa(char * str);
void copy_mem(char * from, char * buffer);
void print_mem_in_screen(char* startPointer,char* buffer);
void print_info_reg(char *data);
char get_char_data(char hex_num);
#endif