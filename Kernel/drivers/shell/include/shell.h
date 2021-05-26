#ifndef _SHELL_H
#define _SHELL_H
#include "../../video/include/video_driver.h"
#include "../../../include/lib.h"
#include "../../timer/include/time.h"

void print_char(unsigned char c);
void _enable_cursor();
void _disable_cursor();
void _set_bg_color(int color);
void _set_text_color(int color);
void _set_text_size(int size);
void _set_cursor_state(char state);
void _internal_print_string(const char * str);
void _internal_print_dec(int i);
void _internal_print_hex(uint64_t h);
int _get_bg_color();
int _get_text_color();
void _set_cursor_pos(int x, int y);
void _get_cursor_pos(int * x, int * y);
void _set_newline_scroll_state(int state);
void _clear_line();
enum common_keys {
    _NEWLINE = '\n',
    _BACKSPACE = '\b',
    _TAB = '\t'
};

#endif