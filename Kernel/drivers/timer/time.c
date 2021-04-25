// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/time.h"

#define MAX_FUNCTIONS 255

typedef struct {
	function f;
	int pid;
	unsigned long int ticks;
	unsigned long int remainingTicks;
} timerFunction;

static timerFunction timerFunctions[MAX_FUNCTIONS] = {{0}};

void timer_restart() {
	for(int i = 0; i < MAX_FUNCTIONS; i++)
		timerFunctions[i].f = 0;
}

void timer_handler() {
	thread_st *t = get_current_thread();
	for(int i = 0; i < MAX_FUNCTIONS && timerFunctions[i].f != 0; i++) {
		if(timerFunctions[i].pid != t->pid) continue;
		timerFunctions[i].remainingTicks--;
		if( timerFunctions[i].remainingTicks == 0 ) {
			timerFunctions[i].remainingTicks = timerFunctions[i].ticks;
			timerFunctions[i].f();
		}
	}			
}

int timer_append_function(function f, unsigned long int ticks, int pid) {
	for(int i = 0; i < MAX_FUNCTIONS; i++) {
		if( timerFunctions[i].f == 0 ) {
			timerFunctions[i].f = f;
			timerFunctions[i].ticks = timerFunctions[i].remainingTicks = ticks;
			timerFunctions[i].pid = pid;
			return 0;
		}

	}
	return -1;
}

int timer_remove_function(function f) {
	int i, j;
	for(i = 0; i < MAX_FUNCTIONS; i++) {
		if( timerFunctions[i].f == f ) {
			timerFunctions[i].f = 0;
			timerFunctions[i].ticks = 0;
			timerFunctions[i].pid = 0;
			for(j = i + 1; j < MAX_FUNCTIONS; j++) {
				timerFunctions[j - 1].f = timerFunctions[j].f;
				timerFunctions[j - 1].remainingTicks = timerFunctions[j].remainingTicks;
				timerFunctions[j - 1].ticks = timerFunctions[j].ticks;
				timerFunctions[j - 1].pid = timerFunctions[j].pid;
			}
			return 0;
		}
	}
	return -1;
}

// https://wiki.osdev.org/Programmable_Interval_Timer - "Using the IRQ to Implement sleep"

