#ifndef _SYSCALLS_H
#define _SYSCALLS_H
#include <stdint.h>
#include "../../drivers/keyboard/include/keyboard.h"
#include "../../drivers/shell/include/shell.h"
#include "../include/lib.h"
#include "../../task/include/process.h"

#define _STDIN 0x1
#define SUCCESS 1
#define ERROR -1
typedef uint64_t syscall(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
// typedef unsigned int size_t;

enum file_descriptors {
    _FD_STD_OUT = 0,
    _FD_STD_IN  = 1,
    _FD_STD_ERR = 2
};

enum syscall_numbers {
    _SYSCALL_READ = 0,
	_SYSCALL_WRITE,
    _SYSCALL_TIME,
    _SYSCALL_SET_BG_COLOR,
    _SYSCALL_SET_TEXT_COLOR,
    _SYSCALL_SET_TEXT_SIZE,
    _SYSCALL_SET_CURSOR_STATE,
    _SYSCALL_INFOREG,
    _SYSCALL_COPY_MEM,
    _SYSCALL_DRAW_MATRIX,
    _SYSCALL_DRAW_RECT,
    _SYSCALL_SET_CURSOR_POS,
    _SYSCALL_GET_CURSOR_POS,
    _SYSCALL_CLEAR_SCREEN,
    _SYSCALL_DRAW_CHARACTER,
    _SYSCALL_SET_NEWLINE_SCROLL_STATE,
    _SYSCALL_CLEAR_LINE,
    _SYSCALL_REGISTER_TIMERTICK_FUNCTION,
    _SYSCALL_UNREGISTER_TIMERTICK_FUNCTION,
    _SYSCALL_BACKUP_KB_BUFFER,
    _SYSCALL_RESTORE_KB_BUFFER,
    _SYSCALL_BACKUP_SCREEN,
    _SYSCALL_RESTORE_SCREEN,
    _SYSCALL_CLEAN_KB_BUFFER,
    _SYSCALL_MALLOC,
    _SYSCALL_FREE,
    _SYSCALL_CREATE_PROCESS
};

#define _SYSCALLS_LAST _SYSCALL_CREATE_PROCESS
#define _SYSCALLS_SIZE (_SYSCALLS_LAST + 1)

syscall syscall_read;
syscall syscall_write;
syscall syscall_time;
syscall syscall_set_bg_color;
syscall syscall_set_text_color;
syscall syscall_set_text_size;
syscall syscall_set_cursor_state;
syscall syscall_inforeg;
syscall syscall_copy_mem;
syscall syscall_draw_matrix;
syscall syscall_draw_rect;
syscall syscall_set_cursor_pos;
syscall syscall_get_cursor_pos;
syscall syscall_clear_screen;
syscall syscall_draw_character;
syscall syscall_set_newline_scroll_state;
syscall syscall_clear_line;
syscall syscall_register_timertick_function;
syscall syscall_unregister_timertick_function;
syscall syscall_backup_kb_buffer;
syscall syscall_restore_kb_buffer;
syscall syscall_backup_screen;
syscall syscall_restore_screen;
syscall syscall_clean_kb_buffer;
syscall syscall_malloc;
syscall syscall_free;
syscall syscall_create_process;

extern syscall * syscalls_table[_SYSCALLS_SIZE];
extern unsigned int get_time(char t);
int read(unsigned int fd, char * buffer, size_t count);
int write(unsigned int fd, char * buffer, size_t count);
void copy_mem(char* from,char* buffer);


#endif