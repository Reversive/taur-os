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
	puts("create_proc - Imprime el PID del proceso creado (max cantidad de procesos a actual es 5 para testear)\n");
	return;
}

void new_process_test_function() {
	printf("Esto todavia no lo deberia ver...\n");
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
			printf("No se puede crear mas procesos!!\n");
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
