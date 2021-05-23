// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/shell.h"



int text_size            = 1;
int _cursor_horizontal   = 0;
int _cursor_vertical     = 0;
int bg_color             = 0x00000000;
int text_color           = 0x04C0CC;
int blink                = 0;
int ignore_newline_scroll= 0;

#define SCALED_CHAR_WIDTH (text_size * CHAR_WIDTH)
#define SCALED_CHAR_HEIGHT (text_size * CHAR_HEIGHT)

void _tick() {
    if(blink) {
        paint_rectangle(_cursor_horizontal, _cursor_vertical, SCALED_CHAR_WIDTH, SCALED_CHAR_HEIGHT, text_color);
    } else {
        paint_rectangle(_cursor_horizontal, _cursor_vertical, SCALED_CHAR_WIDTH, SCALED_CHAR_HEIGHT, bg_color);
    }
    blink = !blink;
}

void _slide_cursor_backwards() {
    if(_cursor_horizontal <= 64) return;
    if(_cursor_horizontal == 0 && _cursor_vertical == 0) return;
    int new_pos = _cursor_horizontal - SCALED_CHAR_WIDTH;
    if( new_pos >= 0) {
        _cursor_horizontal = new_pos;
    } else {
        _cursor_vertical -= SCALED_CHAR_HEIGHT;
        _cursor_horizontal = WIDTH - SCALED_CHAR_WIDTH;
    }
}
void _slide_cursor_newline() {
    _cursor_horizontal = 0;
    if(_cursor_vertical + SCALED_CHAR_HEIGHT < HEIGHT) {
        _cursor_vertical += SCALED_CHAR_HEIGHT;
    } else {
        scroll(SCALED_CHAR_HEIGHT);
    }
}

void _slide_cursor_forward() {
    int new_pos = _cursor_horizontal + SCALED_CHAR_WIDTH;
    if(new_pos < WIDTH) {
        _cursor_horizontal  = new_pos;
    } else if(_cursor_vertical + SCALED_CHAR_HEIGHT < HEIGHT) {
        _cursor_vertical += SCALED_CHAR_HEIGHT;
        _cursor_horizontal = 0;
    } else {
        scroll(SCALED_CHAR_HEIGHT);
        _cursor_horizontal = 0;
    }
}

void _clear_line() {
    paint_rectangle(_cursor_horizontal, _cursor_vertical, WIDTH, SCALED_CHAR_HEIGHT, bg_color);
}

void print_char(unsigned char key) {
    int space_count = 0;
    switch (key)
    {
    case _NEWLINE:
        paint_character(_cursor_horizontal, _cursor_vertical, ' ', text_size, bg_color, bg_color);
        if(ignore_newline_scroll == 0) _slide_cursor_newline();
        break;
    case _BACKSPACE:
        paint_character(_cursor_horizontal, _cursor_vertical, ' ', text_size, bg_color, bg_color);
        _slide_cursor_backwards();
        break;
    case _TAB:
        space_count = _cursor_horizontal % 4;
        if(space_count == 0) space_count = 4;
        for(int i = 0; i < space_count; i++) print_char(' ');
        break;
    default:
        if(key < 0x20 || key > 0x80)
            return;
        paint_character(_cursor_horizontal, _cursor_vertical, key, text_size, text_color, bg_color);
        _slide_cursor_forward();
        break;
    }
    
}

void _internal_print_string(const char * str) {
    int i;
    for(i = 0; str[i] != '\0'; i++) {
        print_char(str[i]);
    }
}

void _set_newline_scroll_state(int state) {
    ignore_newline_scroll = state;
}

int _get_bg_color() {
    return bg_color;
}

int _get_text_color() {
    return text_color;
}


void _enable_cursor() {
    timer_append_function(_tick, 10, 0);
}

void _disable_cursor() {
    timer_remove_function(_tick);
}

void _set_bg_color(int color) {
    bg_color = color;
}

void _set_text_color(int color) {
    text_color = color;
}

void _set_text_size(int size) {
    text_size = size;
}

void _set_cursor_state(char state) {
    if(state == 0x0) {
        _disable_cursor();
    } else {
        _enable_cursor();
    }
}

void _to_string(long num, char * buffer, int mode) {
    int factor = 10;
    if(mode == 1) factor = 16;
    if (num==0){
      buffer[0] = '0';
      return;
    }
    int i=0;
    int j=0;
    while(num > 0){
        if(mode == 0) {
            buffer[i++] = num % factor + '0';
        } else {
            buffer[i++] = get_char_data(num % factor);
        }
        num = num / factor ;
    }
    
    buffer[i--]=0;
     while(j<i){
        char aux = buffer[i];
        buffer[i] = buffer[j];
        buffer[j]=aux;
        j++;
        i--;
    }
}

void _internal_print_dec(int i) {
    char buffer[18];
    _to_string(i, buffer, 0);
    _internal_print_string(buffer);
}

void _internal_print_hex(uint64_t h) {
    char buffer[18];
    _to_string(h, buffer, 1);
    _internal_print_string(buffer);
}

void _set_cursor_pos(int x, int y) {
    _cursor_horizontal = x;
    _cursor_vertical = y;
}

void _get_cursor_pos(int * x, int * y) {
    int c_x = _cursor_horizontal;
    int c_y = _cursor_vertical;
    *x = c_x;
    *y = c_y;
}



