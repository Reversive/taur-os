#include "../include/time.h"
#include "../include/stdio.h"

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

void hexToString(long num, char * buffer){
    if (num==0){
      buffer[0] = '0';
      return;
    }
    int i=0;
    int j=0;
    while(num > 0){
        buffer[i++] = num%16 + '0';
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
  hexToString(get_day_hour(), buffer);
  puts(buffer);
  puts("Hs ");
  hexToString(get_day_minutes(), buffer);
  puts(buffer);
  puts("M ");
  hexToString(get_day_seconds(), buffer);
  puts(buffer);
  puts("S\nDate: ");
  hexToString(get_day(), buffer);
  puts(buffer);
  puts("/");
  hexToString(get_month(), buffer);
  puts(buffer);
  puts("/");
  hexToString(get_year(), buffer);
  puts(buffer);
  puts("\n");
}
