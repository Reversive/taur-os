#include "../include/stdio.h"
#include "../include/inforeg.h"
#include "../include/time.h"

#define ESC_ASCII 27
#define MAX 255

unsigned int consoleNumB;
unsigned int inputReadSizeB = 0;

char inputReadB[MAX] = {0};
char data[136];

unsigned int getchar(void) {
    char c;
    if(sys_read(_FD_STD_IN, &c, 1) == 0) return EOF;
    return (unsigned int)c;
}

unsigned int putchar( char c) {
    if( sys_write(_FD_STD_OUT, &c, 1) == 1 )
        return 1;
    return EOF;
}

int puts(const char *str) {
	for(int i = 0; str[i] != '\0'; i++) {
		if( putchar( str[i] ) == -1 )
            return EOF;
	}
    return 1;
}

unsigned int strlen(char * str){
    int i=0;
    while (str[i]!=0)
    {
        i++;
    }
    return i;
}

void printString(char * str){
    /*Preferimos recorrer una vez para calcular la long del string y hacer un solo llamado a la syscall
    en lugar de hacer un putChar (por ende int80h) hasta encontrar el */
    sys_write(_FD_STD_OUT,str,strlen(str));
    return;
}



void help() {
	puts("Ventana de comandos, pulse Ctrl + 1/2 para cambiar de consola\n");
	puts("Comandos posibles:\n");
	puts("help - Ver comandos\n");
	puts("time - Consultar hora del sistema\n");
	puts("inforeg - Estado de\nregistros. Primero debe capturar con Alt\n");
	puts("printmem 0xDIR - Volcado de memoria\n");
	return;
}

void asignarModulo(char * str) {
	if(commandEql(str, "help")) {
		help();
	}
	else if(commandEql(str,"time")){
		puts("printTime\n");
		
        
    }
	else if(commandEql(str,"inforeg")){
        get_inforeg(data);
		PrintInfoReg(data);
	}
	else if(commandEql(str, "printmem")) {
		//if(!showMemRead(str))
		//	printString("Ingrese una direccion como argumento\n");
	}
	else {
		puts("Ingrese un comando valido.\n");
	}
}

unsigned int commandEql(char * str1, char * str2) {
    while(*str1 == ' ')
        str1++; //Hago un "trim"

    int eql = 1, i;
    for(i = 0; str2[i] != 0; i++) //El de la derecha es el comando a comparar.
        if(str1[i] != str2[i])
            eql = 0;
    if(str1[i] != 0 && str1[i] != ' ')
        eql = 0;
    return eql;    
    }

unsigned int consoleBFinishHandler() {
	inputReadB[inputReadSizeB] = 0;//Le agrego 0 final
	putchar('\n');

	asignarModulo(inputReadB);

	//Reseteamos el buffer
	inputReadSizeB = 0;
	inputReadB[0] = 0;
	return 1;
}

unsigned int finishCharB(char chr) {
	return chr == '\n';
    }

void consoleBKeyHandler(char input) {
	//if(input == 2) {
		/*Existe el caso de que primero comenzo a escribir cosas y luego presiono Alt.
		En ese caso, para que el texto no quede inmerso en el texto viejo, se lo borra y se lo printea
		luego de mostrar la leyendo de captura hecha.*/

		//setRegistersFlag(); //Alt hace captura de registros
		
		//Primero "borro" si es que hay texto impreso antes
	//	for(int i = 0; i < inputReadSizeB; i++)
	//		putChar('\b');
	//	//Imprimo la leyenda
	//	puts("Captura de registros hecha.");
//
	//	//Vuelvo a printear lo que ya estaba, si es que habia
	//	for(int i = 0; i < inputReadSizeB; i++)
	//		putchar(inputReadB[i]);
	//}
     if( input == ESC_ASCII) {
		//IGNORAR

	} else if(input == '\b'){

		if(inputReadSizeB > 0) {
			//Logicamente solo permite borrar si hay algo escrito.
			//Asi evitamos que borrer cosas que no le pertenece.
			inputReadB[inputReadSizeB--] = 0;
			putchar(input);
		}
	} else if(inputReadSizeB < MAX) {
		inputReadB[inputReadSizeB++] = input;
		putchar(input);
	}


	//Si el buffer esta lleno no se lee mas.
}

void PrintInfoReg( char *data){
	char buffer [17]; //16 + 1 para el cero
    char registersName [17][6] = {"R15","R14","R13","R12","R11","R10"," R9"," R8","RAX","RBX","RCX","RDX","RDI","RSI","RBP","RIP","RSP"};  
	int i=0;
	int nByte,idx;
	unsigned char c;
	for(i=0;i<17;i++){
		for ( nByte = i*SIZE_BYTE; nByte <i*SIZE_BYTE+SIZE_BYTE ; nByte++){
			idx=SIZE_BYTE-1-nByte%SIZE_BYTE;
			c=data[nByte] & 0xF0;
			c=c >> 4;
			buffer[idx*2]=getcharData(c);
			c=data[nByte] & 0x0F;
			buffer[idx*2+1]=getcharData(c);
		}
		buffer[16]=0;
		printString(registersName[i]);
		printString("= 0x");
		printString(buffer);
		putchar('\n');
	}
}
char getcharData( char hexaNum) {
    return (hexaNum < 0xA) ? hexaNum + '0' : hexaNum + 'A' - 10;
}