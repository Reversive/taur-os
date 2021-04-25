// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
#include "include/colors.h"
#include "include/console.h"

char console_buffer[MAX] = {0};


int main(int argc, char ** argv) {
	sys_set_text_color(WHITE);
	printf("\nBienvenidos a TaurOS!\n\n");
	sys_set_text_color(LIME);
	help();
	putchar('\n');
	sys_set_cursor_status(_ENABLED);
	
	while(NO_STOP) {
		int c;
		sys_set_text_color(WHITE);
		puts("TaurOS> ");
		sys_set_text_color(LIME);
		while(c = getchar(), c != '\n') {
			if(c != EOF) {
				console_key_handler(c,console_buffer);
			}
		}
		if (is_newline_char(c)){
			console_finish_handler(console_buffer);
		}
		putchar('\n');
	}
	sys_set_cursor_status(_DISABLED);

	return 0x1;
}
