#include "include/time.h"

#define MAX_FUNCTIONS 255

typedef struct {
	function f;
	unsigned long int ticks;
	unsigned long int remainingTicks;
} timerFunction;

static timerFunction timerFunctions[MAX_FUNCTIONS] = {{0}};

void timer_restart() {
	for(int i = 0; i < MAX_FUNCTIONS; i++)
		timerFunctions[i].f = 0;
}

void timer_handler() {

	for(int i = 0; i < MAX_FUNCTIONS && timerFunctions[i].f != 0; i++) {
		timerFunctions[i].remainingTicks--;
		if( timerFunctions[i].remainingTicks == 0 ) {
			timerFunctions[i].remainingTicks = timerFunctions[i].ticks;
			timerFunctions[i].f();
		}
	}			
}

int timer_append_function(function f, unsigned long int ticks) {
	for(int i = 0; i < MAX_FUNCTIONS; i++) {
		if( timerFunctions[i].f == 0 ) {
			timerFunctions[i].f = f;
			timerFunctions[i].ticks = timerFunctions[i].remainingTicks = ticks;
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
			for(j = i + 1; j < MAX_FUNCTIONS; j++) {
				timerFunctions[j - 1].f = timerFunctions[j].f;
				timerFunctions[j - 1].remainingTicks = timerFunctions[j].remainingTicks;
				timerFunctions[j - 1].ticks = timerFunctions[j].ticks;
			}
			return 0;
		}
	}
	return -1;
}

// https://wiki.osdev.org/Programmable_Interval_Timer - "Using the IRQ to Implement sleep"

// https://github.com/atharos1/Leah/blob/master/Kernel/drivers/timer.c

