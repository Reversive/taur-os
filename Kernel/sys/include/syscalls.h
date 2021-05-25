#ifndef _SYSCALLS_H
#define _SYSCALLS_H
#include <stdint.h>
#include "../../drivers/keyboard/include/keyboard.h"
#include "../../drivers/shell/include/shell.h"
#include "../../include/lib.h"
#include "../../dispatcher/include/scheduler.h"
#include "../../mem/include/mm.h"
#include "../../mem/include/buddy.h"
#include "../../sync/include/sem.h"
#include "../../include/pipe.h"

#define _STDIN 0x1
#define SUCCESS 1
#define ERROR -1
#define KILL -1
typedef uint64_t syscall(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

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
    _SYSCALL_CREATE_PROCESS,
    _SYSCALL_GET_PID,
    _SYSCALL_PS,
    _SYSCALL_KILL_PROCESS,
    _SYSCALL_NICE,
    _SYSCALL_BLOCK,
    _SYSCALL_MEM_INFO,
    _SYSCALL_PIPE_OPEN,
    _SYSCALL_PIPE_INFO,
    _SYSCALL_PIPE_CLOSE,
    _SYSCALL_SEM_OPEN,
    _SYSCALL_SEM_WAIT,
    _SYSCALL_SEM_POST,
    _SYSCALL_SEM_CLOSE,
    _SYSCALL_SEM_INFO,
    _SYSCALL_SEM_COUNT,
    _SYSCALL_YIELD,
};

#define _SYSCALLS_LAST _SYSCALL_YIELD
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
syscall syscall_get_pid;
syscall syscall_ps;
syscall syscall_kill_process;
syscall syscall_nice;
syscall syscall_block;
syscall syscall_mem_info;
syscall syscall_pipe_open;
syscall syscall_pipes_info;
syscall syscall_pipe_close;
syscall syscall_sem_open;
syscall syscall_sem_wait;
syscall syscall_sem_post;
syscall syscall_sem_close;
syscall syscall_sem_info;
syscall syscall_sem_count;
syscall syscall_yield;

extern syscall * syscalls_table[_SYSCALLS_SIZE];
extern unsigned int get_time(char t);
int read(unsigned int fd, char * buffer, size_t count);
int write(unsigned int fd, char * buffer, size_t count);
void copy_mem(char* from,char* buffer);


#endif