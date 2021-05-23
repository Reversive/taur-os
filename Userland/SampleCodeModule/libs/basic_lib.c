// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/basic_lib.h"

size_t sys_read(unsigned int fd, char * buffer, size_t length) {
    return (size_t) _syscall(_SYSCALL_READ, fd, (uint64_t) buffer, length, 0, 0);
}

size_t sys_write(unsigned int fd, char * buffer, size_t length) {
    return (size_t) _syscall(_SYSCALL_WRITE, fd, (uint64_t) buffer, length, 0, 0);
}

unsigned int sys_time(char format) {
    return (unsigned int) _syscall(_SYSCALL_TIME, format, 0, 0, 0, 0);
}

void sys_set_bg_color(unsigned int color) {
    _syscall(_SYSCALL_SET_BG_COLOR, color, 0, 0, 0, 0);
}

void sys_set_text_color(unsigned int color) {
    _syscall(_SYSCALL_SET_TEXT_COLOR, color, 0, 0, 0, 0);
}

void sys_set_text_size(unsigned int size) {
    _syscall(_SYSCALL_SET_TEXT_SIZE, size, 0, 0, 0, 0);
}

void sys_set_cursor_status(unsigned char status) {
    _syscall(_SYSCALL_SET_CURSOR_STATE, status, 0, 0, 0, 0);
}

void sys_inforeg( char* data) {
    _syscall(_SYSCALL_INFOREG,(uint64_t)data, 0, 0, 0, 0);
}

void sys_copy_mem( char* from, char* buffer) {
    _syscall(_SYSCALL_COPY_MEM,(uint64_t) from,(uint64_t) buffer, 0, 0, 0);
}

void sys_draw_matrix(int x, int y, int color, char * matrix, int size) {
    _syscall(_SYSCALL_DRAW_MATRIX, x, y, color, (uint64_t) matrix, size);
}

void sys_draw_rect(int x, int y, int w, int h, int color) {
    _syscall(_SYSCALL_DRAW_RECT, x, y, w, h, color);
}

void sys_set_cursor_pos(int x, int y) {
    _syscall(_SYSCALL_SET_CURSOR_POS, x, y, 0, 0, 0);
}

void sys_get_cursor_pos(int * x, int * y) {
    _syscall(_SYSCALL_GET_CURSOR_POS, (uint64_t)x, (uint64_t)y, 0, 0, 0);
}

void sys_clear_screen() {
    _syscall(_SYSCALL_CLEAR_SCREEN, 0, 0, 0, 0, 0);
}

void sys_draw_character(int x, int y, char character, int size, int color) {
    _syscall(_SYSCALL_DRAW_CHARACTER, x, y, character, size, color);
}

void sys_set_newline_scroll_state(int state) {
    _syscall(_SYSCALL_SET_NEWLINE_SCROLL_STATE, state, 0, 0, 0, 0);
}

void sys_clear_line() {
    _syscall(_SYSCALL_CLEAR_LINE, 0, 0, 0, 0, 0);
}

void sys_register_timertick_function(function f, unsigned long ticks, int pid) {
    _syscall(_SYSCALL_REGISTER_TIMERTICK_FUNCTION, (uint64_t)f, ticks, pid, 0, 0);
}

void sys_unregister_timertick_function(function f) {
    _syscall(_SYSCALL_UNREGISTER_TIMERTICK_FUNCTION, (uint64_t)f, 0, 0, 0, 0);
}

void sys_backup_kb_buffer() {
    _syscall(_SYSCALL_BACKUP_KB_BUFFER, 0, 0, 0, 0, 0);
}
void sys_backup_screen() {
    _syscall(_SYSCALL_BACKUP_SCREEN, 0, 0, 0, 0, 0);
}
int sys_restore_kb_buffer() {
    return _syscall(_SYSCALL_RESTORE_KB_BUFFER, 0, 0, 0, 0, 0);
}
int sys_restore_screen() {
    return _syscall(_SYSCALL_RESTORE_SCREEN, 0, 0, 0, 0, 0);
}
void sys_clean_kb_buffer() {
    _syscall(_SYSCALL_CLEAN_KB_BUFFER, 0, 0, 0, 0, 0);
}
void * sys_malloc(size_t size) {
    return (void *)_syscall(_SYSCALL_MALLOC, size, 0, 0, 0, 0);
}
char * sys_pipes_info() {
    return (char *)_syscall(_SYSCALL_PIPE_INFO, 0, 0, 0, 0, 0);
}
int sys_pipe_write(int i, char* addr, int n) {
    return (int)_syscall(_SYSCALL_PIPE_WRITE, (uint64_t) i, (uint64_t)addr, (uint64_t)n, 0, 0);
}
int sys_pipe_read(int i , char* addr, int n) {
    return _syscall(_SYSCALL_PIPE_READ, (uint64_t)i, (uint64_t)addr, (uint64_t)n, 0, 0);
}
int sys_pipe_open(char* name, int fd[2]) {
    return (int)_syscall(_SYSCALL_PIPE_OPEN, (uint64_t)name, (uint64_t)fd, 0, 0, 0);
}
void sys_pipe_close(int index) {
    _syscall(_SYSCALL_PIPE_CLOSE, (int)index,0, 0, 0, 0);
}
int * sys_mem_info() {
    return (int *)_syscall(_SYSCALL_MEM_INFO, 0, 0, 0, 0, 0);
}
void sys_free(void * address) {
    _syscall(_SYSCALL_FREE, (uint64_t) address, 0, 0, 0, 0);
}
pid_t sys_create_process(char *name, main_function f, char **argv) {
    return _syscall(_SYSCALL_CREATE_PROCESS, (uint64_t)name, (uint64_t)f, (uint64_t)argv, 0, 0);
}
pid_t sys_getpid() {
    return _syscall(_SYSCALL_GET_PID, 0, 0, 0, 0, 0);
}
void get_ps(ps_ts *process_list, int *process_count) {
    _syscall(_SYSCALL_PS, (uint64_t)process_list, (uint64_t)process_count, 0, 0, 0);
}
pid_t sys_kill_process(pid_t pid) {
    return _syscall(_SYSCALL_KILL_PROCESS, (uint64_t)pid, 0, 0, 0, 0);
}
pid_t sys_set_niceness(pid_t pid, int priority) {
    return _syscall(_SYSCALL_NICE, (uint64_t)pid, (uint64_t)priority, 0, 0, 0);
}
pid_t sys_block(pid_t pid) {
    return _syscall(_SYSCALL_BLOCK, (uint64_t)pid, 0, 0, 0, 0);
}