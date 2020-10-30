/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
void invalid_opcode_test(void);


int main() {
	
	unsigned int hour = get_day_hour();
	unsigned int minutes = get_day_minutes();
	unsigned int seconds = get_day_seconds();
	unsigned int test = getchar();
	while (test == -1)
	{
		test = getchar();
		if(test != -1) return test;
	}
	
	return test;
}