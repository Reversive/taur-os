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
		print_string(startPointer_string);
		print_string(": ");
		for(int j=0;j<8;j++){
			putchar(buffer[i*8+j*2]);
			putchar(buffer[i*8+j*2+1]);
			putchar(' ');
		}
		startPointer=startPointer+8;
		putchar('\n');
	}
}

void print_info_reg( char *data){
	char buffer [17]; 
    char register_names [17][6] = {"R15","R14","R13","R12","R11","R10"," R9"," R8","RAX","RBX","RCX","RDX","RDI","RSI","RBP","RIP","RSP"};
	int i=0;
	int nByte,idx;
	unsigned char c;
	for(i=0;i<17;i++){
		for ( nByte = i*SIZE_BYTE; nByte <i*SIZE_BYTE+SIZE_BYTE ; nByte++){
			idx=SIZE_BYTE-1-nByte%SIZE_BYTE;
			c=data[nByte] & 0xF0;
			c=c >> 4;
			buffer[idx*2]=get_char_data(c);
			c=data[nByte] & 0x0F;
			buffer[idx*2+1]=get_char_data(c);
		}
		buffer[16]=0;
		print_string(register_names[i]);
		print_string("= 0x");
		print_string(buffer);
		putchar('\n');
	}
}

char get_char_data(char hex_num) {
    return (hex_num < 0xA) ? hex_num + '0' : hex_num + 'A' - 10;
}