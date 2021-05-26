#include "../include/basic_lib.h"
#include "../include/stdio.h"
#include "../include/_loader.h"
#include "include/philo.h"
#include "include/test_util.h"
#include "unistd.h"

#define MIN_PHIL 5
#define MAX_PHIL 20

static int state[MAX_PHIL];

#define THINKING 2
#define HUNGRY 1
#define EATING 0

#define LEFT (phnum + cant - 1) % cant
#define RIGHT (phnum + 1) % cant

static int numPhil = 0;
static int cant;

static semInfo_t mutex;
static semInfo_t S[MAX_PHIL];	// cubiertos
static char * names[MAX_PHIL];
static int philPID[MAX_PHIL];

void print_philos(int phnum) {
	for (int j = 0; j < cant; j++) {
        if(state[j] == EATING) {
			printf(" E ");
		}
        else printf(" . ");
    }
    printf("\n");
}

static void put_names(){
    for (int i = 0; i < MIN_PHIL; i++) {
        names[i] = sys_malloc(3);
        if (names[i] == NULL) {
            printf("ERROR: Malloc\n");
            return;
        }
        names[i] = itoa(i, names[i], 10);
	    strcpy(S[i].name, names[i]);
    }   
}

void test(int phnum) {
	if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		state[phnum] = EATING;
		sys_yield();
		print_philos(phnum);
		sys_sem_post(S[phnum].name);
	}
}

// take up chopsticks
void take_fork(int phnum) {
	sys_sem_wait(mutex.name);
	state[phnum] = HUNGRY;
	test(phnum);
	sys_sem_post(mutex.name);
	sys_sem_wait(S[phnum].name);
	sys_yield();
}

// put down chopsticks
void put_fork(int phnum) {
	sys_sem_wait(mutex.name);
	state[phnum] = THINKING;
	test(LEFT);
	test(RIGHT);
	sys_sem_post(mutex.name);
}

int philosopher(int argc, char ** argv) {
    int i = numPhil++;
	while (1) {
		sys_yield();
		take_fork(i);
		sys_yield();
		put_fork(i);
	}
	return 0;
}

void kill_philo(int i){
    sys_sem_wait(mutex.name);
    if(S[i].value > 0) {
        sys_sem_wait(S[i].name);
    }    
    if(sys_kill_process(philPID[i]) == -1) {
        printf("ERROR: Kill %d\n", philPID[i]);
    }
    if(sys_sem_close(S[i].name) != 0) {
        printf("ERROR: Close Sem %s\n", S[i].name);
    }
    cant--;
    numPhil--;
    sys_sem_post(mutex.name);
    sys_sem_close(mutex.name);   
}

void exit_philo(){
    for (int i = cant-1; i >= 0; i--) {
        kill_philo(i);
    }
    for (int i = 0; i < MIN_PHIL; i++) {
       sys_free(names[i]);
    }
    sys_sem_close(mutex.name);   
}

int add_philo(int idx) {
	sys_sem_wait(mutex.name);
	
	if(idx>=MAX_PHIL) {
		return -1;
	}
	
    names[idx] = itoa(idx, names[idx], 10);
	strcpy(S[idx].name, names[idx]);
	sys_sem_open(names[idx], 1);
	int wait[2] = {0};
	if(S[0].value == 1) {
		wait[0] = 1;
		sys_sem_wait(S[0].name);
	}
	if(S[cant-1].value == 1) {
		wait[1] = 1;
		sys_sem_wait(S[cant-1].name);
	}
    philPID[idx] = execv(names[idx], philosopher,(char*[]){NULL}, 0);
	cant++;
	if(wait[0] == 1) {
		sys_sem_post(S[0].name);
	}
	if(wait[1] == 1) {
		sys_sem_post(S[idx-1].name);
	}

	sys_sem_post(mutex.name);
	return 0;
}

int philos(int argc, char ** argv){

	printf("Problema de los filosofos comensales:\n");
    printf("Para agregar un filosofo, presione 'a' (Max: %d)\n", MAX_PHIL);
    printf("Para remover un filosofo, presione 'r' (Min: %d)\n", MIN_PHIL);
    printf("Para terminar el programa, presione 'q'\n");

	cant = MIN_PHIL;
	put_names();

	strcpy(mutex.name, "mutex");
	sys_sem_open("mutex", 1);

	int i;
	for(i = 0; i < cant; i++) {
		sys_sem_open(S[i].name, 1);
	}
	for (i = 0; i < cant; i++) {
    	philPID[i] = execv(names[i], philosopher,(char*[]){NULL}, 0);

	}

	printf("\n%d filosofos comen y piensan...\n",cant);

	int running = 1;

	while(running) {
		int c = getchar();
		switch (c) {
		case 'a':
			if(cant+1 < MAX_PHIL) {
				printf("Invitando otro filosofo a la mesa...\n");
				add_philo(cant);
			} else {
				printf("Hay muchos comensales, no invite mas");
			}
			break;
		case 'r':
			printf("LEYO R\n");
			if(cant > 0) {
				kill_philo(cant-1);
			}
			if(cant == 0) {
				printf("Todos se fueron. Levantando la mesa...\n");
				running = 0;
			}
			break;
		case 'q':
			exit_philo();
			printf("Ahuyentando a los filosofos...\n");
			running = 0;
			break;
		default:
			break;
		}
	}

	return 0;
}