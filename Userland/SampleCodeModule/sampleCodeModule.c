/* sampleCodeModule.c */
#include "include/basic_lib.h"

void invalid_opcode_test(void);


int main() {
	
	unsigned int hour = sys_time(0x4);
	unsigned int minutes = sys_time(0x2);
	unsigned int seconds = sys_time(0x0);

	return minutes;
}