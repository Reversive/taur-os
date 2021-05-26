// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "print_mem.h"

unsigned int errorFlag;

char  s[200] = {0};

void copy_mem(char* from,char* buffer){
    sys_copy_mem(from,buffer);
}
void fill0(char* s){
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		s[i] = 0;
	}
	
}
char* info_mem( char * str) {
	while(*str == ' ')
		str++; 
	while(*str != ' ')
		str++; 
	while(*str == ' ')
		str++;
	if(*str == 0)
		return 0; //No recibio argumento
	if(*str == '0' && (*(str+1)=='x' || *(str+1)=='X') && is_hexa_digit(*(str+2))) {
		str++; 
		str++;
		char* startPointer= parse_str_to_hexa(str);
        if(errorFlag)
			return 0;
		char buffer[65]; 
        copy_mem(startPointer, buffer);
		
		
		return print_mem_in_screen(startPointer,buffer);;

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
		number *= 16;
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


char* print_mem_in_screen(char* startPointer,char* buffer){
	fill0(s);
	int first = 1;
	char buff[2] = {0};
	char startPointer_string[8];
	for(int i=0;i<4;i++){
		hex_to_string((long) startPointer,startPointer_string);
		if(first){
			first = 0;
			strcpy(s, startPointer_string);
		}
		else{
			strcat(s, startPointer_string);
		}
		strcat(s, ": ");
		for(int j=0;j<8;j++){
			buff[0] = buffer[i*8+j*2];
			strcat(s, buff);
			buff[0] = buffer[i*8+j*2+1];
			strcat(s, buff);
			strcat(s, " ");
		}
		startPointer=startPointer+8;
		strcat(s, "\n");
	}
	return s;
}


char * print_info_reg( char *data){
	char buffer [17]; 
	int first = 1;
	fill0(s);
    char register_names [17][6] = {"R15","R14","R13","R12","R11","R10"," R9"," R8","RBX","RCX","RDX","RDI","RBP","RIP","RSI","RAX","RSP"};
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
		if(first){
			strcpy(s,register_names[i]);
			first = 0;
		}
		strcat(s,register_names[i]);
		strcat(s, "= 0x");
		strcat(s, buffer);
		strcat(s, "\n");
	}
	return s;
}

char get_char_data(char hex_num) {
    return (hex_num < 0xA) ? hex_num + '0' : hex_num + 'A' - 10;
}