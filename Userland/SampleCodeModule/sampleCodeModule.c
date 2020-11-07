/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
#include "include/colors.h"
#include "include/console.h"
#include "include/chess_bitmap.h"
#include "include/chess.h"

char console_buffer[MAX] = {0};


int main() {
	sys_set_cursor_status(_ENABLED);
	
	while(1) {
		char c;
		if(chess_state==PLAYING || chess_state==ENDED) {
			sys_set_newline_scroll_state(1);
			sys_set_cursor_pos(0, 720);
			sys_clear_line();
		}
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
