// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/console.h"
#include "apps/include/test_sync.h"
#include "basic_lib.h"
#include "stdio.h"
#include <stdint.h>

#define NO_PID -1
#define MAX_SEMS 256
#define MAX_PROC 50

unsigned int console_num;
unsigned int input_read_size = 0;
int rotation = 0;
int in_foreground = 1;


char data[136];
void invalid_opcode_test(void);
void help() {
	sys_write(fd_pipe[1], "Comandos posibles:\n", 20);
	sys_write(fd_pipe[1], "help - Ver comandos.\n", 22);
	sys_write(fd_pipe[1], "time - Consultar hora del sistema.\n", 36);
	sys_write(fd_pipe[1], "ps - Lista los procesos actuales.\n", 35);
	sys_write(fd_pipe[1], "kill <pid> - Mata el proceso del PID especificado.\n", 52);
	sys_write(fd_pipe[1], "nice <pid> <prio> - Cambia la prioridad de un proceso dado su PID y la nueva prioridad.\n", 89);
	sys_write(fd_pipe[1], "block <pid> - Cambia el estado de un proceso entre bloqueado y listo dado su PID.\n", 83);
	sys_write(fd_pipe[1], "inforeg - Estado de registros.\n", 32);
	sys_write(fd_pipe[1], "endless - Crea un proceso que no termina.\n", 43);
	sys_write(fd_pipe[1], "ending - Crea un proceso que termina.\n", 39);
	sys_write(fd_pipe[1], "loop - Crea proceso loop donde imprime su PID cada una cierta cantidad de tiempo.\n", 83);
	sys_write(fd_pipe[1], "printmem 0xDIR - Volcado de memoria.\n", 38);
	sys_write(fd_pipe[1], "mem_info - Muestra el estado actual de la memoria\n", 51);
	sys_write(fd_pipe[1], "pipes - Muestra el estado de los pipes\n", 40);
	sys_write(fd_pipe[1], "sems - Informacion sobre todos los semaforos\n", 46);
	sys_write(fd_pipe[1], "cat - Imprime el stdin tal como lo recibe\n", 43);
	sys_write(fd_pipe[1], "wc - Cuenta la cantidad de lineas del input\n", 45);
	sys_write(fd_pipe[1], "filter - Filtra las vocales del input\n", 39);
	sys_write(fd_pipe[1], "philo - Implementa el problema de los filosofos comensales\n", 60);
	sys_write(fd_pipe[1], "Tests:\n", 8);
	sys_write(fd_pipe[1], "mm_test - Corre el test del Memory Manager.\n", 45);
	sys_write(fd_pipe[1], "pr_test - Corre el test de procesos.\n", 38);
	sys_write(fd_pipe[1], "prio_test - Corre el test de prioridades.\n", 43);
	sys_write(fd_pipe[1], "sync_test - Corre el test de sincronizacion de procesos con semaforos\n", 71);
	sys_write(fd_pipe[1], "no_sync_test - Corre el test de sincronizacion de procesos sin semaforos\n", 74);
	sys_write(fd_pipe[1], "pipes_test - test de los pipes\n", 32);
	sys_write(fd_pipe[1], "shm_test - test de shm\n", 24);
	return;
}

parameters param_list[PROGRAM_COUNT] = { { "9", NULL }, { "Hola", "Como Estas", NULL }, {NULL}};


int endless_proc(int argc, char **argv) {
	while(1) {
		bussy_wait(MINOR_WAIT);
	}
}

int ending_proc(int argc, char **argv) {
	return 0;
}

void mem_info(uint64_t total, uint64_t free) {
	printfd("ESTADO DE LA MEMORIA\n");
	printfd("%d / %d",total-free, total);
}

void sems() {
	semInfo_t * buffer = sys_malloc(sizeof(semInfo_t));
	int semsCount = sys_sems_count();
	if(semsCount>0) {
		char tmp[10][2];
		printf("%10s%10s%10s%s\n","SEM_ID","NAME","VALUE","BLOCKED_PIDS");
		for(int idx=0; idx<semsCount; idx++) {
			sys_sem_info(idx, buffer);
			printf("%10s%10s%10s",	itoa((uint64_t)buffer->semId, tmp[0], 10),
									buffer->name,
									itoa((uint64_t)buffer->value, tmp[1], 10));
			if(buffer->blockedProcesses[0] != NO_PID) {
				printfd("{ %d ",buffer->blockedProcesses[0]);
				int cantBlockProc = (buffer->blockedLast)%MAX_PROC - (buffer->blockedFirst)%MAX_PROC;
				for(int i=1; i<cantBlockProc; i++) {
					printfd("%d ",buffer->blockedProcesses[i]);
				}
				printfd("}\n");
			}
			printf("\n");
		}
	} else {
		printfd("No semaphores running.\n");
	}
}

void sh_ps() {
	ps_ts process_buffer[50];
	int process_count = 0;
	char tmp[20][4];
	get_ps(process_buffer, &process_count);
	printfd("%6s%16s%16s%12s%12s%10s%s\n", "PID", "NAME", "FOREGROUND", "PRIORITY", "STATUS", "STACK", "BASE POINTER");
	for(int i = 0; i < process_count; i++) {
		int status = process_buffer[i].status; 
		printfd("%6s%16s%16s%12s%12s%10s%X\n",	itoa((uint64_t)process_buffer[i].pid, tmp[0], 10),
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
			printfd("Proceso eliminado correctamente.\n");
		} else {
			printfd("PID invalido.\n");
		}
	} else {
		printfd("PID invalido.\n");
	}
}

void sh_nice(char *str) {
	pid_t pid, priority;
	if(scanf(str, "%d%d", &pid, &priority) > 0) {
		if(nice(pid, priority) == pid) {
			printfd("Prioridad cambiada correctamente.\n");
		} else {
			printfd("PID invalido.\n");
		}
	} else {
		printfd("PID invalido.\n");
	}
}

void sh_block(char *str) {
	pid_t pid;
	if(scanf(str, "%d", &pid) > 0 && pid != 0) {
		if(block(pid) == pid) {
			printfd("Proceso bloqueado/desbloqueado correctamente.\n");
		} else {
			printfd("PID invalido.\n");
		}
	} else {
		printfd("PID invalido.\n");
	}
}

void print_execve_output(pid_t pid) {
	if(pid != INVALID_PID)
	{
		printfd("Se creo el proceso con pid %d\n", pid);
	} else {
		printfd("No se pueden crear mas procesos o no hay suficiente memoria\n");
	}
}

int assign_module(char * str) {
	if(command_equal(str, "help") ) {
		help();
		sys_sem_post("pipe");
	}
	else if(command_equal(str,"time") ){
		char* time = print_time();
        sys_write(fd_pipe[1], time, strlen(time));
		sys_sem_post("pipe");
    }
	else if(command_equal(str,"inforeg") ){
        get_inforeg(data);
		char* info_reg = print_info_reg(data);
		sys_write(fd_pipe[1], info_reg, strlen(info_reg));
		sys_sem_post("pipe");
	}
	else if(command_equal(str, "printmem") ) {
		char* printmem = info_mem(str);
		if(!printmem)
			printfd("Ingrese una direccion como argumento\n");
		else
			sys_write(fd_pipe[1], printmem, strlen(printmem));
		sys_sem_post("pipe");
	}
	else if(command_equal(str, "ps") ) {
		sh_ps();
		sys_sem_post("pipe");
    }
	else if(command_equal(str, "loop")) {
		pid_t pid = execv("loop", loop, param_list[1], in_foreground);
		print_execve_output(pid);
	}
	else if(command_equal(str, "endless")) {
		pid_t pid = execv("endless_proc", endless_proc, param_list[2], in_foreground);
		print_execve_output(pid);
	}
	else if(command_equal(str, "ending")) {
		pid_t pid = execv("ending_proc", ending_proc, param_list[2], in_foreground);
		print_execve_output(pid);
	}
	else if(command_equal(str, "kill")) {
		sh_kill(str);
		sys_sem_post("pipe");
	}
	else if(command_equal(str, "nice")) {
		sh_nice(str);
		sys_sem_post("pipe");
	}
	else if(command_equal(str, "block")) {
		sh_block(str);
		sys_sem_post("pipe");
	} 
	else if(command_equal(str, "mm_test")) {
		pid_t pid = execv("mm_test", main_test_mm, param_list[2], in_foreground);
		print_execve_output(pid);
	}
	else if(command_equal(str, "prio_test")) {
		execv("prio_test", main_test_prio, param_list[2], in_foreground);
	}
	else if(command_equal(str, "pr_test")) {
		execv("pr_test", test_processes_main, param_list[2], in_foreground);
	} 
	else if(command_equal(str, "mem_info")) {
		int * info = sys_mem_info();
		mem_info(info[0], info[1]);
		sys_sem_post("pipe");
	}
	else if(command_equal(str, "pipes")) {
		char * info = sys_pipes_info();
		printfd("%s\n", info);
		sys_sem_post("pipe");
	}
	else if(command_equal(str, "pipes_test")) {
		test_pipe();
		sys_sem_post("pipe");
	}
	else if(command_equal(str, "sync_test")) {
		execv("sync_test", test_sync, param_list[2], in_foreground);
	} 
	else if(command_equal(str, "no_sync_test")) {
		execv("no_sync_test", test_no_sync, param_list[2], in_foreground);
	}
	else if(command_equal(str, "sems")) {
		sems();
		sys_sem_post("pipe");
	}
	else if(command_equal(str, "wc")) {
		execv("wc", wc, param_list[2], in_foreground);
	}
	else if(command_equal(str, "cat")) {
		execv("cat", cat, param_list[2], in_foreground);
	}
	else if(command_equal(str, "filter")) {
		execv("filer", filter, param_list[2], in_foreground);
	}
	else if(command_equal(str, "philo")) {
		execv("philo", philos, (char*[]){NULL}, in_foreground);
	}
	else if(command_equal(str, "shm_test")) {
		execv("shm_test", shm_test, (char*[]){NULL}, in_foreground);
	}
	else {
		if(fd_pipe[1] == 0)
			printfd("Ingrese un comando valido.\n");
		sys_sem_post("pipe");
		return 1;
	}
	return 0;
}


unsigned int command_equal(char * s1, char * s2) {
	char str1[strlen(s1)];
	char str2[strlen(s2)];
	strcpy(str1, s1);
	strcpy(str2, s2);
	int j = 0;
    while(str1[j] == ' ') {
        j++;
	}
	
	for(int i = 0; str1[i] != 0; i++) {
		if(str1[i] == '&') in_foreground = 0;
	}
    int eql = 1, i;
    for(i = 0; str2[i] != 0; i++)
        if(str1[i] != str2[i])
            eql = 0;
    if(str1[i] != 0 && str1[i] != ' ')
        eql = 0;
	
    return eql;
}

unsigned int is_newline_char(char chr) {
	return chr == '\n';
}

int pipe_function(char* input){
	char aux_input[strlen(input)];
	strcpy(aux_input, input);
	char * found = strchr (aux_input, '|');
	if(found == 0)
		return -1;
	int len_l = found - aux_input + 1;
	int len_r = strlen(aux_input) - (found- aux_input);
	char left[len_l];
	char right[len_r];
	strcpy(left, aux_input);
	strcpy(right, found+1);
	left[len_l-1]=0;
	right[len_r-1] = 0;

	fd_pipe[1] = sys_pipe_open("pipes");
	int fd_pipe_aux = fd_pipe[1];

	input_read_size = len_l-1;
	fd_pipe[0] = 1;	// stdin es keyboard
					// stdout es el pipe
	sys_sem_open("pipe", 0);
	int aux = console_finish_handler(left);
	strcpy(left, input);
	sys_sem_wait("pipe");
	if(aux){
		sys_write(fd_pipe[1], left, len_l-1);
	}
	input_read_size = len_r -1;

	fd_pipe[0] = fd_pipe_aux; // stdin es el pipe
	fd_pipe[1] = 0;			  // stdout es la shell
	console_finish_handler(right);
	sys_sem_wait("pipe");
	fd_pipe[0] = 1;		// stdin es keyboard
	fd_pipe[1] = 0;		// stdout es shell

	sys_pipe_close(fd_pipe_aux);
	sys_sem_close("pipe");
	return 0;

}

unsigned int console_finish_handler(char* input_buffer) {
	input_buffer[input_read_size] = 0;
	putchar('\n');
	unsigned int ret = 0;
	if(pipe_function(input_buffer) == -1)
		if(assign_module(input_buffer)==1)
			ret = 1;

	input_read_size = 0;
	input_buffer[0] = 0;
	return ret;
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