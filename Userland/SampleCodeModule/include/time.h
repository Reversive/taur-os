#ifndef _TIME_H
#define _TIME_H

#include "basic_lib.h"
unsigned int get_day_seconds();
unsigned int get_day_minutes();
unsigned int get_day_hour();
unsigned int get_day();

void print_time();
void hex_to_string(long num, char * buffer);
#endif
