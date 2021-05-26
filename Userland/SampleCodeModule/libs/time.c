// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/time.h"


unsigned int get_day_seconds() {
    return sys_time(0x0);
}

unsigned int get_day_minutes() {
    return sys_time(0x2);
}

unsigned int get_day_hour() {
    return sys_time(0x4);
}

unsigned int get_day() {
    return sys_time(0x7);
}

unsigned int get_month() {
    return sys_time(0x8);
}

unsigned int get_year() {
    return sys_time(0x9);
}


char string[40] = {0};
char * print_time() {
  char buffer[3];
  strcpy(string, "Time: ");
  hex_to_string(get_day_hour(), buffer);
  strcat(string, buffer);
  strcat(string,"hs " );
  hex_to_string(get_day_minutes(), buffer);
  strcat(string, buffer);
  strcat(string,"m ");
  hex_to_string(get_day_seconds(), buffer);
  strcat(string, buffer);
  strcat(string,"s\nDate: ");
  hex_to_string(get_day(), buffer);
  strcat(string, buffer);
  strcat(string,"/");
  hex_to_string(get_month(), buffer);
  strcat(string, buffer);
  strcat(string,"/");
  hex_to_string(get_year(), buffer);
  strcat(string, buffer);
  strcat(string,"\n");
  return string;
}
