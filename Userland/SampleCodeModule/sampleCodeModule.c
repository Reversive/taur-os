/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
void invalid_opcode_test(void);

static char tester = 'a';
int main() {
	unsigned int hour = get_day_hour();
	unsigned int minutes = get_day_minutes();
	unsigned int seconds = get_day_seconds();
	
	while(1) {
		char c;
		puts("TPE> ");
		while(c = getchar(), c != '\n') {
			if(c != EOF) {
				putchar(c);
			}
		}

		putchar('\n');
	}

	
	return 0x1;
}