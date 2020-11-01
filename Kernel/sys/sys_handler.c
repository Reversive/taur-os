#include "include/sys_handler.h"


syscall * syscalls_table[_SYSCALLS_SIZE] = {
	[_SYSCALL_READ] = syscall_read,
	[_SYSCALL_WRITE] = syscall_write,
    [_SYSCALL_TIME] = syscall_time,
    [_SYSCALL_SET_BG_COLOR] = syscall_set_bg_color,
    [_SYSCALL_SET_TEXT_COLOR] = syscall_set_text_color,
    [_SYSCALL_SET_TEXT_SIZE] = syscall_set_text_size,
    [_SYSCALL_SET_CURSOR_STATE] = syscall_set_cursor_state,
    [_SYSCALL_INFOREG] = syscall_inforeg

};


uint64_t sys80handler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    if( rdi < 0 || rdi > _SYSCALLS_SIZE) return -1;
    return syscalls_table[rdi](rsi, rdx, rcx, r8);
}

uint64_t syscall_read(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    unsigned int fd = (unsigned int) rsi;
    char * buffer = (char *) rdx;
    size_t count = (size_t) rcx;
    return read(fd, buffer, count);
}

uint64_t syscall_write(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    unsigned int fd = (unsigned int) rsi;
    char * buffer = (char *) rdx;
    size_t count = (size_t) rcx;
    return write(fd, buffer, count);
}

uint64_t syscall_time(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    char setting = (char) rsi;
    return get_time(setting);
}

uint64_t syscall_set_bg_color(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    unsigned int color = (unsigned int) rsi;
    _set_bg_color(color);
    return SUCCESS;
}

uint64_t syscall_set_text_color(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    unsigned int color = (unsigned int) rsi;
    _set_text_color(color);
    return SUCCESS;
}

uint64_t syscall_set_text_size(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    unsigned int size = (unsigned int) rsi;
    _set_text_size(size);
    return SUCCESS;
}

uint64_t syscall_set_cursor_state(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    unsigned char status = (unsigned char) rsi;
    _set_cursor_state(status);
    return SUCCESS;
}

uint64_t syscall_inforeg(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
    unsigned char* data = (unsigned char*) rsi;
    get_registers(data);
    return SUCCESS;
}