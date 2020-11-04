/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
#include "include/colors.h"
#include "include/console.h"
#include "include/chess_bitmap.h"


int main() {
	for(int i = 0; i < 8; i+=2) {
		sys_draw_square(i*80, 300, 80, 0x282828);
	}
	for(int i = 1; i < 8; i+=2) {
		sys_draw_square(i*80, 300, 80, 0xD7D7D7);
	}

	for(int i = 0; i < 8; i++) {
		draw_pawn(i*80, 300, 0xFFFFFF);
	}
	
	draw_tower(0, 380, 0xFFFFFF);
	draw_horse(80, 380, 0xFFFFFF);
	draw_bishop(160, 380, 0xFFFFFF);
	draw_king(240, 380, 0xFFFFFF);
	draw_queen(320, 380, 0xFFFFFF);
	draw_bishop(400, 380, 0xFFFFFF);
	draw_horse(480, 380, 0xFFFFFF);
	draw_tower(560, 380, 0xFFFFFF);
	sys_set_cursor_status(_ENABLED);
	while(1) {
		char c;
		putchar('\n');
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
