// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/sys_handler.h"


syscall * syscalls_table[_SYSCALLS_SIZE] = {
	[_SYSCALL_READ] = syscall_read,
	[_SYSCALL_WRITE] = syscall_write,
    [_SYSCALL_TIME] = syscall_time,
    [_SYSCALL_SET_BG_COLOR] = syscall_set_bg_color,
    [_SYSCALL_SET_TEXT_COLOR] = syscall_set_text_color,
    [_SYSCALL_SET_TEXT_SIZE] = syscall_set_text_size,
    [_SYSCALL_SET_CURSOR_STATE] = syscall_set_cursor_state,
    [_SYSCALL_INFOREG] = syscall_inforeg,
    [_SYSCALL_COPY_MEM] = syscall_copy_mem,
    [_SYSCALL_DRAW_MATRIX] = syscall_draw_matrix,
    [_SYSCALL_DRAW_RECT] = syscall_draw_rect,
    [_SYSCALL_SET_CURSOR_POS] = syscall_set_cursor_pos,
    [_SYSCALL_GET_CURSOR_POS] = syscall_get_cursor_pos,
    [_SYSCALL_CLEAR_SCREEN] = syscall_clear_screen,
    [_SYSCALL_DRAW_CHARACTER] = syscall_draw_character,
    [_SYSCALL_SET_NEWLINE_SCROLL_STATE] = syscall_set_newline_scroll_state,
    [_SYSCALL_CLEAR_LINE] = syscall_clear_line,
    [_SYSCALL_REGISTER_TIMERTICK_FUNCTION] = syscall_register_timertick_function,
    [_SYSCALL_UNREGISTER_TIMERTICK_FUNCTION] = syscall_unregister_timertick_function,
    [_SYSCALL_BACKUP_KB_BUFFER] = syscall_backup_kb_buffer,
    [_SYSCALL_RESTORE_KB_BUFFER] = syscall_restore_kb_buffer,
    [_SYSCALL_BACKUP_SCREEN] = syscall_backup_screen,
    [_SYSCALL_RESTORE_SCREEN] = syscall_restore_screen,
    [_SYSCALL_CLEAN_KB_BUFFER] = syscall_clean_kb_buffer,
    [_SYSCALL_MALLOC] = syscall_malloc,
    [_SYSCALL_FREE] = syscall_free,
    [_SYSCALL_CREATE_PROCESS] = syscall_create_process,
    [_SYSCALL_GET_PID] = syscall_get_pid,
    [_SYSCALL_PS] = syscall_ps,
    [_SYSCALL_KILL_PROCESS] = syscall_kill_process,
    [_SYSCALL_NICE] = syscall_nice,
    [_SYSCALL_BLOCK] = syscall_block
};


uint64_t sys80handler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    if(rdi >= _SYSCALLS_SIZE) return ERROR;
    return syscalls_table[rdi](rsi, rdx, rcx, r8, r9);
}