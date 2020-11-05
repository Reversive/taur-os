#include "include/console.h"
int player_turn = 0;

int current_player_one_seconds = 300;
int current_player_two_seconds = 300;
void player_one_timer() {
	print_string_by_pos(700, 500, itoa(current_player_one_seconds, 10), 0xFFFFFF, 2);
	current_player_one_seconds -= 1;
}

void player_two_timer() {
	print_string_by_pos(800, 500, itoa(current_player_two_seconds, 10), 0xFF0000, 2);
	current_player_two_seconds -= 1;
}

unsigned int console_num;
unsigned int input_read_size = 0;

char input_buffer[MAX] = {0};
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
	if(command_equal(str, "help")) {
		help();
	}
	else if(command_equal(str,"time")){
        print_time();
    }
	else if(command_equal(str,"inforeg")){
        get_inforeg(data);
		print_info_reg(data);
	}
	else if(command_equal(str, "printmem")) {
		if(!info_mem(str))
			print_string("Ingrese una direccion como argumento\n");
	}
    else if(command_equal(str, "opcode")) {
        invalid_opcode_test();
    }
    else if(command_equal(str, "div0")) {
        int b = 5 / 0;
    }
	else if(command_equal(str, "chess")) {
		//int status = 0;
		//while(status == JUGANDO) { status = join_chess(); }
	}
	else if (command_equal(str,"move")){
		int x1,x2,y1,y2;
		parse_move(str,&x1,&y1,&x2,&y2);//A2 A3
		if(player_turn == 0) {
			player_turn = 1;
			sys_unregister_timertick_function(player_one_timer);
			sys_register_timertick_function(player_two_timer, 18);
		} else {
			player_turn = 0;
			sys_unregister_timertick_function(player_two_timer);
			sys_register_timertick_function(player_one_timer, 18);
		}
		if (check_movement(x1,y1,x2,y2)){
			move_chess_piece(x1,y1,x2,y2);
		} else {
			puts("Error");
		}
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

unsigned int console_finish_handler() {
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

void console_key_handler(char input) {

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
