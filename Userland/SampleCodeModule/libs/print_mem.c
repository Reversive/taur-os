#include "print_mem.h"

unsigned int errorFlag;

void print_mem(char* from,char* buffer){
    sys_print_mem(from,buffer);
}

int info_mem( char * str) {
	
	while(*str == ' ')
		str++; //Hacemos un trim al principio
	while(*str != ' ')
		str++; //Salteamos el printmem
	while(*str == ' ' && *str != 0)
		str++; //Salteo espacios intermedios
	if(*str == 0)
		return 0; //No recibio argumento
	if(*str == '0' && (*(str+1)=='x' || *(str+1)=='X') && is_hexa_digit(*(str+2))) {
		str++; //Me salteo el 0x inicial
		str++;
		char* startPointer= parse_str_to_hexa(str);
        if(errorFlag)
			return 0;
		char buffer[65]; //Se necesitan de N * 2 + 1 siendo N la cantidad de bytes a leer
        print_mem(startPointer, buffer);
		print_mem_in_screen(startPointer,buffer);
		putchar('\n');
		return 1;

	} else {
		return 0;
	}
}

int is_hexa_digit(char digit) {
	return (digit >= '0' && digit <= '9') || (digit >= 'A' && digit <= 'F') || (digit >= 'a' && digit <= 'f');
}

char * parse_str_to_hexa(char * str) {
	errorFlag = 0;
	uint64_t number = 0;
	unsigned int len = 0;
	while(*str != 0 && *str != ' ' && !errorFlag) {
		if(!is_hexa_digit(*str))
			errorFlag = 1;
		number *= 16; //Multiplico por 16 para correr todo un lugar a la izquierda
		if(*str >= '0' && *str <= '9')
			number += (*str - '0');
		else if(*str >= 'A' && *str <= 'F')
			number += (*str - 'A');
		else
			number += (*str - 'a');
		str++;
		len++;
	}
	if(len > 16)
		errorFlag = 1;
	return (char *)number;
}

int is_number(char c){
	return c>='0' && c<='9';
}


void print_mem_in_screen(char* startPointer,char* buffer){
	char startPointer_string[8];
	for(int i=0;i<4;i++){
		hex_to_string((long) startPointer,startPointer_string);
		printString(startPointer_string);
		printString(": ");
		for(int j=0;j<8;j++){
			putchar(buffer[i*8+j*2]);
			putchar(buffer[i*8+j*2+1]);
			putchar(' ');
		}
		startPointer=startPointer+8;
		putchar('\n');
	}
}