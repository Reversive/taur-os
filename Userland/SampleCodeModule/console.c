// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/console.h"


unsigned int console_num;
unsigned int input_read_size = 0;
int rotation = 0;


char data[136];
void invalid_opcode_test(void);
void help() {
	printf("Comandos posibles:\n");
	printf("help - Ver comandos.\n");
	printf("time - Consultar hora del sistema.\n");
	printf("inforeg - Estado de registros.\n");
	printf("printmem 0xDIR - Volcado de memoria.\n");
	printf("mm_test - Corre el test del Memory Manager.\n");
	printf("pr_test - Corre el test de procesos.\n");
	printf("prio_test - Corre el test de prioridades.\n");
	printf("endless - Crea un proceso que no termina.\n");
	printf("ending - Crea un proceso que termina.\n");
	printf("loop - Crea proceso loop donde imprime su PID con un saludo cada 2 segundos.\n");
	printf("ps - Lista los procesos actuales.\n");
	printf("kill <pid> - Mata el proceso del PID especificado.\n");
	printf("nice <pid> <prio> - Cambia la prioridad de un proceso dado su PID y la nueva prioridad.\n");
	printf("block <pid> - Cambia el estado de un proceso entre bloqueado y listo dado su PID.\n");
	printf("mem_info - Muestra el estado actual de la memoria\n");
	return;
}

parameters param_list[PROGRAM_COUNT] = { { "Hola", NULL }, { "Hola", "Como Estas", NULL }};


int endless_proc(int argc, char **argv) {
	while(1) {
		bussy_wait(MINOR_WAIT);
	}
}

int ending_proc(int argc, char **argv) {
	return 0;
}

void sh_ps() {
	ps_ts process_buffer[50];
	int process_count = 0;
	char tmp[20][4];
	get_ps(process_buffer, &process_count);
	printf("%6s%16s%16s%12s%12s%10s%s\n", "PID", "NAME", "FOREGROUND", "PRIORITY", "STATUS", "STACK", "BASE POINTER");
	for(int i = 0; i < process_count; i++) {
		int status = process_buffer[i].status; 
		if(status == 3) continue;
		printf("%6s%16s%16s%12s%12s%10s%X\n",	itoa((uint64_t)process_buffer[i].pid, tmp[0], 10),
												process_buffer[i].process_name,
												itoa((uint64_t)process_buffer[i].foreground, tmp[1], 10),
												itoa((uint64_t)process_buffer[i].priority, tmp[2], 10),
												status == READY ? "READY" : status == BLOCKED ? "BLOCKED" : "KILLED",
												itoa((uint64_t)process_buffer[i].cs, tmp[3], 16),
												(uint64_t)process_buffer[i].bp);
	}
}

void sh_kill(char *str) {
	pid_t pid;
	if(scanf(str, "%d", &pid) > 0) {
		if(kill(pid) == pid) {
			printf("Proceso eliminado correctamente.\n");
		} else {
			printf("PID invalido.\n");
		}
	} else {
		printf("PID invalido.\n");
	}
}

void sh_nice(char *str) {
	pid_t pid, priority;
	if(scanf(str, "%d%d", &pid, &priority) > 0) {
		if(nice(pid, priority) == pid) {
			printf("Prioridad cambiada correctamente.\n");
		} else {
			printf("PID invalido.\n");
		}
	} else {
		printf("PID invalido.\n");
	}
}

void sh_block(char *str) {
	pid_t pid;
	if(scanf(str, "%d", &pid) > 0) {
		if(block(pid) == pid) {
			printf("Proceso bloqueado/desbloqueado correctamente.\n");
		} else {
			printf("PID invalido.\n");
		}
	} else {
		printf("PID invalido.\n");
	}
}

void print_execve_output(pid_t pid) {
	if(pid != INVALID_PID)
	{
		printf("Se creo el proceso con pid %d\n", pid);
	} else {
		printf("No se pueden crear mas procesos o no hay suficiente memoria\n");
	}
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
	else if(command_equal(str, "ps") ) {
		sh_ps();
    }
	else if(command_equal(str, "loop")) {
		pid_t pid = execv("loop", loop, param_list[1]);
		print_execve_output(pid);
	}
	else if(command_equal(str, "endless")) {
		pid_t pid = execv("endless_proc", endless_proc, param_list[0]);
		print_execve_output(pid);
	}
	else if(command_equal(str, "ending")) {
		pid_t pid = execv("ending_proc", ending_proc, param_list[0]);
		print_execve_output(pid);
	}
	else if(command_equal(str, "kill")) {
		sh_kill(str);
	}
	else if(command_equal(str, "nice")) {
		sh_nice(str);
	}
	else if(command_equal(str, "block")) {
		sh_block(str);
	} 
	else if(command_equal(str, "mm_test")) {
		pid_t pid = execv("mm_test", main_test_mm, param_list[0]);
		print_execve_output(pid);
	}
	else if(command_equal(str, "prio_test")) {
		execv("prio_test", main_test_prio, (char*[]){NULL});
	}
	else if(command_equal(str, "pr_test")) {
		execv("process_test", test_processes_main, (char*[]){NULL});
	} 
	else if(command_equal(str, "mem_info")) {
		int * info = sys_mem_info();
		printf("ESTADO DE LA MEMORIA\nTOTAL\t\t LIBRE\t\t OCUPADA\n");
		printf("%d\t\t%d\t\t%d\n", info[0], info[1], info[0] - info[1]);
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

