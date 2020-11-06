#include "include/console.h"


unsigned int console_num;
unsigned int input_read_size = 0;
int chess_state = NOT_PLAYING;
int rotation = 0;


char data[136];
void invalid_opcode_test(void);
void help() {
	puts("Ventana de comandos, pulse Ctrl + 1/2 para cambiar de consola\n");
	puts("Comandos posibles:\n");
	puts("help - Ver comandos\n");
	puts("time - Consultar hora del sistema\n");
	puts("inforeg - Estado de registros. Primero debe capturar con Alt\n");
	puts("printmem 0xDIR - Volcado de memoria\n");
    puts("opcode - Generar excepcion de codigo de operacion invalido\n");
    puts("div0 - Generar excepcion de division por cero\n");
	return;
}

void assign_module(char * str) {
	if(command_equal(str, "help") && (chess_state == NOT_PLAYING || chess_state == PAUSED)) {
		help();
	}
	else if(command_equal(str,"time") && (chess_state == NOT_PLAYING || chess_state == PAUSED)){
        print_time();
    }
	else if(command_equal(str,"inforeg") && (chess_state == NOT_PLAYING || chess_state == PAUSED)){
        get_inforeg(data);
		print_info_reg(data);
	}
	else if(command_equal(str, "printmem") && (chess_state == NOT_PLAYING || chess_state == PAUSED)) {
		if(!info_mem(str))
			print_string("Ingrese una direccion como argumento\n");
	}
    else if(command_equal(str, "opcode") && (chess_state == NOT_PLAYING || chess_state == PAUSED)) {
        invalid_opcode_test();
    }
    else if(command_equal(str, "div0") && (chess_state == NOT_PLAYING || chess_state == PAUSED)) {
        int b = 5 / 0;
    }
	else if (command_equal(str,"move") && chess_state == PLAYING){
		move_piece(str);
	}
	else if(command_equal(str, "chess") && (chess_state == NOT_PLAYING || chess_state == PAUSED) ) {
		join_chess();
	} else if(command_equal(str, "exit") && chess_state == PLAYING) {
		close_chess(NOT_PLAYING);
	}
	else {
		puts("Ingrese un comando valido.\n");
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
	if(input == '\t'){
		if (chess_state == PLAYING){
			close_chess(PAUSED);
			sys_set_text_color(WHITE);
			putchar('\n');
			puts("TaurOS> ");
			sys_set_text_color(LIME);
		}
		else{
			join_chess();
			sys_set_text_color(WHITE);
			puts("TaurOS> ");
			sys_set_text_color(LIME);
		}
		
	}
	else if (input=='r' && chess_state==1) {
		rotation_chess_table();
		rotation++;
		print_chess_table(printeable_chess_table);
	}
	

    else if( input == ESC_ASCII) {

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
