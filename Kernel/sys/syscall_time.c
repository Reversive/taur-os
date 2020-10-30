#include "include/syscall_time.h"
/* ESTE ARCHIVO Y EL .H SE VAN A PASAR A USERLAND, PERO LA MAYORIA SE BORRA, NO HACE FALTA HACER LA CONVERSION HEX=>DEC */
extern unsigned int get_time(char t);

int get_time_format(int t){
    return (t/16)*10+(t%16);
}

void sys_get_time (char t, int * result){
  *result = get_time_format(get_time(t));
  return;
}

void sys_get_day (int * result){
  *result = get_time(6);
  return;
}

/* En kernel por motivos de debug.*/
void num_to_string(long num, char * buffer) {
    int i=0;
    int j=0;
    while(num > 0){
        buffer[i++] = num%10 + '0';
        num = num / 10 ;
    }
    char aux;
    buffer[i--]=0;
     while(j<i){
        aux = buffer[i];
        buffer[i] = buffer[j];
        buffer[j]=aux;
        j++;
        i--;
    }
}

/* En kernel y probado de forma directa por motivos de debug.*/
void print_time() {
	int hours,minutes,seconds,day;
	sys_get_time(4,&hours);
	sys_get_time(2,&minutes);
	sys_get_time(0,&seconds);
	sys_get_day(&day);

  char buffer [3];
	ncPrint("Time: ");
  num_to_string(hours,buffer);
	ncPrint(buffer);
	ncPrint(" hs ");
  num_to_string(minutes,buffer);
	ncPrint(buffer);
	ncPrint(" m ");
  num_to_string(seconds,buffer);
	ncPrint(buffer);
	ncPrint(" s");
	ncNewline();
	ncPrint("Day: ");
  num_to_string(day,buffer);
	ncPrint(buffer);
	ncNewline();
  return;
}