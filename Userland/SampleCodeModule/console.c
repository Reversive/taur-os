#include "include/console.h"


unsigned int console_num;
unsigned int input_read_size = 0;
int rotation = 0;


char data[136];
void invalid_opcode_test(void);
void help() {
	puts("Comandos posibles:\n");
	puts("help - Ver comandos\n");
	puts("time - Consultar hora del sistema\n");
	puts("inforeg - Estado de registros.\n");
	puts("printmem 0xDIR - Volcado de memoria\n");
    puts("opcode - Generar excepcion de codigo de operacion invalido\n");
    puts("div0 - Generar excepcion de division por cero\n");
	puts("mm_test - Corre el test del Memory Manager\n");
	puts("create_proc - Crea 3 procesos, imprime sus pid's y los ejecuta\n");
	return;
}

int new_process_test_function(int argc, char ** argv) {
	while(1) printf("[PROCESO %d]Hola\n", get_pid());
}

int new_process2_test_function(int argc, char ** argv) {
	while(1) printf("[PROCESO %d]Como\n", get_pid());
}

int new_process3_test_function(int argc, char ** argv) {
	while(1) printf("[PROCESO %d]Estas\n", get_pid());
}

void assign_module(char * str) {
	if(command_equal(str, "help") ) {
		help();
	}
	else if(command_equal(str,"time") ){
        print_time();
    }
	else if(command_equal(str,"inforeg") ){
        get_inforeg(data);
		print_info_reg(data);
	}
	else if(command_equal(str, "printmem") ) {
		if(!info_mem(str))
			printf("Ingrese una direccion como argumento\n");
	}
    else if(command_equal(str, "opcode") ) {
        invalid_opcode_test();
    }
    else if(command_equal(str, "div0") ) {
        int a = 0;
		int b = 5;
		b /= a;
    }
	else if(command_equal(str, "create_proc")) {
		char **argv = {0};
		pid_t resultado = execv("Probando", new_process_test_function, argv);
		if(resultado != -1)
		{
			printf("Se creo el proceso con pid %d\n", resultado);
		} else {
			printf("No se pueden crear mas procesos o no hay suficiente memoria\n");
		}
		pid_t resultado2 = execv("Probando2", new_process2_test_function, argv);
		if(resultado2 != -1)
		{
			printf("Se creo el proceso con pid %d\n", resultado2);
		} else {
			printf("No se pueden crear mas procesos o no hay suficiente memoria\n");
		}

		pid_t resultado3 = execv("Probando3", new_process3_test_function, argv);
		if(resultado3 != -1)
		{
			printf("Se creo el proceso con pid %d\n", resultado3);
		} else {
			printf("No se pueden crear mas procesos o no hay suficiente memoria\n");
		}


	} 
	else if(command_equal(str, "mm_test")) {
		test_mm();
	} else {
		printf("Ingrese un comando valido.\n");
	}
}

unsigned int command_equal(char * str1, char * str2) {
    while(*str1 == ' ')
        str1++;
    int eql = 1, i;
    for(i = 0; str2[i] != 0; i++)
        if(str1[i] != str2[i])
            eql = 0;
    if(str1[i] != 0 && str1[i] != ' ')
        eql = 0;
    return eql;
    }

unsigned int console_finish_handler(char* input_buffer) {
	input_buffer[input_read_size] = 0;
	putchar('\n');
	assign_module(input_buffer);
	input_read_size = 0;
	input_buffer[0] = 0;
	return 1;
}

unsigned int is_newline_char(char chr) {
	return chr == '\n';
}

void console_key_handler(char input,char* input_buffer) {
	if( input == ESC_ASCII) {
	} else if(input == '\b'){
		if(input_read_size > 0) {
			input_buffer[input_read_size--] = 0;
			putchar(input);
		}
	} else if(input_read_size < MAX) {
		input_buffer[input_read_size++] = input;
		putchar(input);
	}
}

void print_string_by_pos(int x, int y, char * str, int color, int size) {
	for(int i = 0; str[i] != 0; i++) {
		sys_draw_character(x + i * size * 16, y , str[i], size, color);
	}
}
