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



void print_time() {
  char buffer[3];
  puts("Time: ");
  hex_to_string(get_day_hour(), buffer);
  puts(buffer);
  puts("hs ");
  hex_to_string(get_day_minutes(), buffer);
  puts(buffer);
  puts("m ");
  hex_to_string(get_day_seconds(), buffer);
  puts(buffer);
  puts("s\nDate: ");
  hex_to_string(get_day(), buffer);
  puts(buffer);
  puts("/");
  hex_to_string(get_month(), buffer);
  puts(buffer);
  puts("/");
  hex_to_string(get_year(), buffer);
  puts(buffer);
  puts("\n");
}
