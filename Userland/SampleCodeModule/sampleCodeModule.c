/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
#include "include/colors.h"
#include "include/console.h"
#include "include/chess_bitmap.h"
#include "include/chess.h"

int main() {
	
	

	join_chess();

	sys_set_cursor_status(_ENABLED);
	while(1) {
		char c;
		sys_set_text_color(WHITE);
		puts("TaurOS> ");
		sys_set_text_color(LIME);
		while(c = getchar(), c != '\n') {
			if(c != EOF) {
				console_key_handler(c);
			}
		}
		if (is_newline_char(c)){
			console_finish_handler();
		}
		putchar('\n');
	}
	sys_set_cursor_status(_DISABLED);

	return 0x1;
}
