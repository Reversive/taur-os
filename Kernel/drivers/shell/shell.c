#include "include/shell.h"

int size                 = 1;
int _cursor_horizontal   = 0;
int _cursor_vertical     = 0;
int bg_color             = 0x00000000;
int color                = 0x04C0CC;
static int blink         = 0;

void _tick() {
    if(blink) {
        paint_rectangle(_cursor_horizontal, _cursor_vertical, CHAR_WIDTH, CHAR_HEIGHT, color);
    } else {
        paint_rectangle(_cursor_horizontal, _cursor_vertical, CHAR_WIDTH, CHAR_HEIGHT, bg_color);
    }
    blink = !blink;
}

void _enable_cursor() {
    timer_append_function(_tick, 14);
}

void _disable_cursor() {
    timer_remove_function(_tick);
}


void _slide_cursor(int qty) {
    if(qty < 0) paint_rectangle(_cursor_horizontal, _cursor_vertical, CHAR_WIDTH, CHAR_HEIGHT, bg_color);
    _cursor_horizontal += CHAR_WIDTH * qty * size;
}


void print_char(unsigned char key) {
    switch (key)
    {
    case _NEWLINE:
        break;
    case _BACKSPACE:
        _slide_cursor(-1);
        break;
    default:
        if(key < 0x20 || key > 0x80)
            return;
        paint_character(_cursor_horizontal, _cursor_vertical, key, size, color, bg_color);
        _slide_cursor(1);
        break;
    }
    
}