#include "../include/time.h"
#include "../include/stdio.h"
#include "../include/print_mem.h"

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

void hex_to_string(long num, char * buffer){
    if (num==0){
      buffer[0] = '0';
      return;
    }
    int i=0;
    int j=0;
    while(num > 0){
        buffer[i++] = get_char_data(num%16);
        num = num / 16 ;
    }
    char aux; //j apunta al comienzo del buffer, i al final
    buffer[i--]=0;
     while(j<i){
        aux = buffer[i];
        buffer[i] = buffer[j];
        buffer[j]=aux;
        j++;
        i--;
    }
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
