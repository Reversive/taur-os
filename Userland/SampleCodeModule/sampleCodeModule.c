/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
#include "include/colors.h"
#include "include/console.h"
#include "include/chess_bitmap.h"
#include "include/chess.h"

int main() {
	
	join_chess();
	sys_set_newline_scroll_state(1);
	sys_set_cursor_status(_ENABLED);
	
	sys_draw_character(650, 20, '8', 3, 0xFFFFFF);
	sys_draw_character(650, 100, '7', 3, 0xFFFFFF);
	sys_draw_character(650, 180, '6', 3, 0xFFFFFF);
	sys_draw_character(650, 260, '5', 3, 0xFFFFFF);
	sys_draw_character(650, 340, '4', 3, 0xFFFFFF);
	sys_draw_character(650, 420, '3', 3, 0xFFFFFF);
	sys_draw_character(650, 500, '2', 3, 0xFFFFFF);
	sys_draw_character(650, 580, '1', 3, 0xFFFFFF);
	sys_draw_character(20, 650, 'A', 3, 0xFFFFFF);
	sys_draw_character(100, 650, 'B', 3, 0xFFFFFF);
	sys_draw_character(180, 650, 'C', 3, 0xFFFFFF);
	sys_draw_character(260, 650, 'D', 3, 0xFFFFFF);
	sys_draw_character(340, 650, 'E', 3, 0xFFFFFF);
	sys_draw_character(420, 650, 'F', 3, 0xFFFFFF);
	sys_draw_character(500, 650, 'G', 3, 0xFFFFFF);
	sys_draw_character(580, 650, 'H', 3, 0xFFFFFF);
	while(1) {
		char c;
		sys_set_cursor_pos(0, 720);
		sys_clear_line();
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
