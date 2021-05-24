#ifndef _BASIC_LIB_H
#define _BASIC_LIB_H
#include <stdint.h>
#define NULL ((void *)0)

typedef unsigned int size_t;
typedef int pid_t;
#define STDIN 0x1
#define NO_STOP 1
#define UINT_MAX 0xffffffff

uint64_t _syscall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
typedef void (*function)(void);
typedef int (*main_function)(int argc, char **argv);
unsigned int sys_time(char format);
size_t sys_read(unsigned int fd, char * buffer, size_t length);
size_t sys_write(unsigned int fd, char * buffer, size_t length);
void sys_set_cursor_status(unsigned char status);
void sys_set_text_size(unsigned int size);
void sys_set_text_color(unsigned int color);
void sys_set_bg_color(unsigned int color);
void sys_inforeg( char* data);
void sys_copy_mem(char* from, char* buffer);
void sys_draw_matrix(int x, int y, int color, char * matrix, int size);
void sys_draw_rect(int x, int y, int w, int h, int color);
void sys_set_cursor_pos(int x, int y);
void sys_get_cursor_pos(int * x, int * y);
void sys_clear_screen();
void sys_draw_character(int x, int y, char character, int size, int color);
void sys_set_newline_scroll_state(int state);
void sys_clear_line();
void sys_register_timertick_function(function f, unsigned long ticks, int pid);
void sys_unregister_timertick_function(function f);
void sys_backup_kb_buffer();
void sys_backup_screen();
int sys_restore_kb_buffer();
int sys_restore_screen();
void sys_clean_kb_buffer();
void * sys_malloc(size_t size);
void sys_free(void * address);
int *sys_mem_info();
char* sys_pipes_info();
int sys_pipe_open(char *name);
void sys_pipe_close(int i);
pid_t sys_create_process(char *name, main_function f, char **argv);
pid_t sys_getpid();
pid_t sys_kill_process(pid_t pid);
pid_t sys_set_niceness(pid_t pid, int priority);
pid_t sys_block(pid_t pid);

typedef enum { READY = 0, BLOCKED, KILLED } process_status_et;

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
};

enum status {
    _DISABLED = 0,
    _ENABLED
};

typedef struct {
    pid_t pid;
    char *process_name;
    int foreground;
    int priority;
    void *cs;
    void *bp;
    process_status_et status;
} ps_ts;


void get_ps(ps_ts *process_list, int *process_count);

#endif