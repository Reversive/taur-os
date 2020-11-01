#include "../include/basic_lib.h"

size_t sys_read(unsigned int fd, char * buffer, size_t length) {
    return (size_t) _syscall(_SYSCALL_READ, fd, (uint64_t) buffer, length, 0);
}

size_t sys_write(unsigned int fd, char * buffer, size_t length) {
    return (size_t) _syscall(_SYSCALL_WRITE, fd, (uint64_t) buffer, length, 0);
}

unsigned int sys_time(char format) {
    return (unsigned int) _syscall(_SYSCALL_TIME, format, 0, 0, 0);
}

void sys_set_bg_color(unsigned int color) {
    _syscall(_SYSCALL_SET_BG_COLOR, color, 0, 0, 0);
}

void sys_set_text_color(unsigned int color) {
    _syscall(_SYSCALL_SET_TEXT_COLOR, color, 0, 0, 0);
}

void sys_set_text_size(unsigned int size) {
    _syscall(_SYSCALL_SET_TEXT_SIZE, size, 0, 0, 0);
}

void sys_set_cursor_status(unsigned char status) {
    _syscall(_SYSCALL_SET_CURSOR_STATE, status, 0, 0, 0);
}





