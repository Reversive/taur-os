// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/syscalls.h"



uint64_t syscall_read(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    unsigned int fd = (unsigned int) rsi;
    char * buffer = (char *) rdx;
    size_t count = (size_t) rcx;
    return read(fd, buffer, count);
}

uint64_t syscall_write(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    unsigned int fd = (unsigned int) rsi;
    char * buffer = (char *) rdx;
    size_t count = (size_t) rcx;
    return write(fd, buffer, count);
}

uint64_t syscall_time(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    char setting = (char) rsi;
    return get_time(setting);
}

uint64_t syscall_set_bg_color(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    unsigned int color = (unsigned int) rsi;
    _set_bg_color(color);
    return SUCCESS;
}

uint64_t syscall_set_text_color(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    unsigned int color = (unsigned int) rsi;
    _set_text_color(color);
    return SUCCESS;
}

uint64_t syscall_set_text_size(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    unsigned int size = (unsigned int) rsi;
    _set_text_size(size);
    return SUCCESS;
}

uint64_t syscall_set_cursor_state(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    unsigned char status = (unsigned char) rsi;
    _set_cursor_state(status);
    return SUCCESS;
}

uint64_t syscall_inforeg(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    unsigned char* data = (unsigned char*) rsi;
    get_registers(data);
    return SUCCESS;
}

uint64_t syscall_copy_mem(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    char* from = (char*) rsi;
    char* buffer = (char*) rdx;
    copy_mem(from,buffer);
    return SUCCESS;
}

uint64_t syscall_draw_matrix(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int x = (int) rsi;
    int y = (int) rdx;
    int color = (int) rcx;
    char * m = (char *) r8; 
    int size = (int) r9;
    paint_matrix(x, y, color, size, m);
    
    return SUCCESS;
}

uint64_t syscall_draw_rect(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int x = (int) rsi;
    int y = (int) rdx;
    int w = (int) rcx;
    int h = (int) r8;
    int color = (int) r9;
    paint_rectangle(x, y, w, h, color);
    return SUCCESS;
}

uint64_t syscall_set_cursor_pos(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int x = (int) rsi;
    int y = (int) rdx;
    if(x < 0 || x > WIDTH || y < 0 || y > HEIGHT) return ERROR;
    _set_cursor_pos(x, y);
    return SUCCESS;
}

uint64_t syscall_get_cursor_pos(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int * x = (int *) rsi;
    int * y = (int *) rdx;
    _get_cursor_pos(x, y);
    return SUCCESS;
}

uint64_t syscall_clear_screen(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    clear_screen(_get_bg_color());
    return SUCCESS;
}

uint64_t syscall_draw_character(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int x = (int) rsi;
    int y = (int) rdx;
    if(x < 0 || x > WIDTH || y < 0 || y > HEIGHT) return ERROR;
    char c = (char) rcx;
    int size = (int) r8;
    int color = (int) r9;
    paint_character(x, y, c, size, color, _get_bg_color());
    return SUCCESS;

}

uint64_t syscall_set_newline_scroll_state(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int state = (int) rsi;
    _set_newline_scroll_state(state);
    return SUCCESS;
}

uint64_t syscall_clear_line(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    _clear_line();
    return SUCCESS;
}

uint64_t syscall_register_timertick_function(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    function f = (function) rsi;
    unsigned long ticks = (unsigned long) rdx;
    pid_t pid = (pid_t)rcx;
    timer_append_function(f, ticks, pid);
    return SUCCESS;
}

uint64_t syscall_unregister_timertick_function(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    function f = (function) rsi;
    timer_remove_function(f);
    return SUCCESS;
}

uint64_t syscall_backup_kb_buffer(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    backup_kb_buffer();
    return SUCCESS;
}

uint64_t syscall_restore_kb_buffer(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int response = restore_kb_buffer();
    if(response == ERROR) return ERROR;
    return SUCCESS;
}

uint64_t syscall_backup_screen(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    backup_screen();
    return SUCCESS;
}

uint64_t syscall_restore_screen(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int response = restore_backup_screen();
    if(response == ERROR) return ERROR;
    return SUCCESS;
}

uint64_t syscall_clean_kb_buffer(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    clean_kb_buffer();
    return SUCCESS;
}


uint64_t syscall_malloc(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    size_t size = (size_t) rsi;
    void *response = malloc(size);
    if(response ==  NULL) return ERROR;
    return (uint64_t)response;
}

uint64_t syscall_free(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    void * address = (void*) rsi;
    free(address);
    return SUCCESS;
}

uint64_t syscall_create_process(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    char *name = (char *)rsi;
    void *code = (void *)rdx;
    char **argv = (char**)rcx;
    return create_process(name, code, argv, MIN_PAGE_AMOUNT * PAGE_SIZE, 0, 5);
}

uint64_t syscall_get_pid(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    return get_current_pid();
}

uint64_t syscall_ps(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    ps_ts *process_buffer = (ps_ts *)rsi;
    int *p_count = (int *)rdx;
    ps(process_buffer, p_count);
    return SUCCESS;
}

uint64_t syscall_kill_process(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    pid_t pid = (pid_t)rsi;
    return kill_process(pid, KILL);
}

uint64_t syscall_nice(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    pid_t pid = (pid_t)rsi;
    size_t priority = (size_t)rdx;
    return set_process_niceness(pid, priority);
}

uint64_t syscall_block(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    pid_t pid = (pid_t)rsi;
    process_status_et current_status = get_process_state(pid);
    process_status_et new_status = current_status == READY ? BLOCKED : (current_status == BLOCKED ? READY : INVALID);
    return set_process_state(pid, new_status);
}

uint64_t syscall_mem_info(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    int * mem_info = memInfo();
    return (uint64_t) mem_info;
}

int read(unsigned int fd, char * buffer, size_t count) {
    unsigned int bytes_read = 0;
    char popped_key;
    switch (fd)
    {
        case _FD_STD_IN:
            for( bytes_read = 0; bytes_read < count && (popped_key = getchar()) != -1; bytes_read++ )
                buffer[bytes_read] = popped_key;
            break;
    }
    
    return bytes_read;
}


int write(unsigned int fd, char * buffer, size_t count) {
    unsigned int bytes_written = 0;
    switch (fd)
    {
        case _FD_STD_OUT:
            for(bytes_written = 0; bytes_written < count; bytes_written++)
                print_char(buffer[bytes_written]);
            break;

        case _FD_STD_ERR:
            break;
    }
    
    return bytes_written;
}

void copy_mem(char * from, char * buffer) {
	int _byte_idx;
	

	for(_byte_idx = 0; _byte_idx < 32; _byte_idx++) {
		//Por cada byte leo 2 valores hexa
		unsigned char aux = from[_byte_idx] & 0xF0;// & 1111 0000
		aux = aux >> 4;
		buffer[_byte_idx * 2] = get_char_data(aux);
		aux = from[_byte_idx] & 0x0F;// & 0000 1111
		buffer[_byte_idx * 2 + 1] = get_char_data(aux);
	}
	buffer[_byte_idx * 2] = 0;
}