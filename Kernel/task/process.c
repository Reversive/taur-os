#include "include/process.h"

process_st *processes[MAX_PROCESS_COUNT] = {NULL};

pid_t get_available_pid() {
    pid_t current_pid = UNAVAILABLE;
    for(int current_process = 0; current_process < MAX_PROCESS_COUNT; current_process++) {
        if(processes[current_process] == NULL) {
            current_pid = current_process;
            break;
        }
    }
    return current_pid;
}

size_t calculate_heap_size(size_t size) {
    return size == EMPTY ? size : size;
}

size_t set_process_name(process_st * process, char *name) {
    process->process_name = (char *) malloc(strnlen(name));
    if(process->process_name == NULL) return NOT_ENOUGH_MEMORY;
    my_strcpy(process->process_name, name);
    return SUCCESS;
}

pid_t create_process(char *name, address_t code, char **argv, size_t stack, size_t heap) {
    
    pid_t pid = get_available_pid();
    if(pid == UNAVAILABLE || code == NULL) return UNAVAILABLE;
    process_st *process = (process_st *) malloc(sizeof(process));
    if(process == NULL) return NOT_ENOUGH_MEMORY;
    process->pid = pid;
    process->status = ALIVE;
    if(set_process_name(process, name) == NOT_ENOUGH_MEMORY) return NOT_ENOUGH_MEMORY;
    size_t heap_size = calculate_heap_size(heap);
    process->heap.base = heap_size == EMPTY ? NULL : (address_t) malloc(heap_size);
    if(process->heap.base == NULL) return NOT_ENOUGH_MEMORY;
    process->heap.size = heap_size;
    processes[process->pid] = process;
    thread_st *thread = create_thread(code, argv, stack, process->threads, process->pid);
    if(thread == NULL) return NOT_ENOUGH_MEMORY;
    processes[process->pid]->threads[thread->tid] = thread;
    return process->pid;
}


