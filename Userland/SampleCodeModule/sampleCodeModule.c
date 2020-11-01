/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
#include "include/colors.h"
void invalid_opcode_test(void);

int main() {

	sys_set_cursor_status(_ENABLED);
	while(1) {
		char c;
		sys_set_text_color(WHITE);
		puts("TaurOS> ");
		sys_set_text_color(LIME);
		while(c = getchar(), c != '\n') {
			if(c != EOF) {
				putchar(c);
			}
		}

		putchar('\n');
	}
	sys_set_cursor_status(_DISABLED);

	
	return 0x1;
}