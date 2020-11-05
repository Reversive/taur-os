#ifndef _BASIC_LIB_H
#define _BASIC_LIB_H
#include <stdint.h>
typedef unsigned int size_t;
#define STDIN 0x1
uint64_t _syscall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
typedef void (*function)(void);
unsigned int sys_time(char setting);
size_t sys_read(unsigned int fd, char * buffer, size_t length);
size_t sys_write(unsigned int fd, char * buffer, size_t length);
void sys_set_cursor_status(unsigned char status);
void sys_set_text_size(unsigned int size);
void sys_set_text_color(unsigned int color);
void sys_set_bg_color(unsigned int color);
void sys_inforeg( char* data);
void sys_print_mem( char* from, char* buffer);
void sys_draw_matrix(int x, int y, int color, char * matrix, int size);
void sys_draw_square(int x, int y, int size, int color);
void sys_set_cursor_pos(int x, int y);
void sys_get_cursor_pos(int * x, int * y);
void sys_clear_screen();
void sys_draw_character(int x, int y, char character, int size, int color);
void sys_set_newline_scroll_state(int state);
void sys_clear_line();
void sys_register_timertick_function(function f, unsigned long ticks);
void sys_unregister_timertick_function(function f);

enum syscall_numbers {
    _SYSCALL_READ = 0,
	_SYSCALL_WRITE,
    _SYSCALL_TIME,
    _SYSCALL_SET_BG_COLOR,
    _SYSCALL_SET_TEXT_COLOR,
    _SYSCALL_SET_TEXT_SIZE,
    _SYSCALL_SET_CURSOR_STATE,
    _SYSCALL_INFOREG,
    _SYSCALL_PRINT_MEM,
    _SYSCALL_DRAW_MATRIX,
    _SYSCALL_DRAW_SQUARE,
    _SYSCALL_SET_CURSOR_POS,
    _SYSCALL_GET_CURSOR_POS,
    _SYSCALL_CLEAR_SCREEN,
    _SYSCALL_DRAW_CHARACTER,
    _SYSCALL_SET_NEWLINE_SCROLL_STATE,
    _SYSCALL_CLEAR_LINE,
    _SYSCALL_REGISTER_TIMERTICK_FUNCTION,
    _SYSCALL_UNREGISTER_TIMERTICK_FUNCTION
};

enum status {
    _DISABLED = 0,
    _ENABLED
};

#endif