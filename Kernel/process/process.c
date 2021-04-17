#include "include/process.h"
process_st *processes[MAX_PROCESS_COUNT];

pid_t get_available_pid() {
    pid_t current_pid = UNAVAILABLE;
    for(int current_process = 0; current_process < MAX_PROCESS_COUNT; current_process++) {
        if(processes[current_process] == NULL) current_pid = current_process;
    }
    return current_pid;
}

size_t calculate_heap_size(size_t size) {
    return size == EMPTY ? size : size * PAGE_SIZE;
}

size_t set_process_name(process_st * process, char *name) {
    process->process_name = malloc(strlen(name));
    if(process->process_name == NULL) return NOT_ENOUGH_MEMORY;
    strcpy(process->process_name, name);
    return SUCCESS;
}

pid_t create_process(char *name, address_t code, address_t *argv, size_t stack, size_t heap) {
    pid_t pid = get_available_pid();
    if(pid == UNAVAILABLE || code == NULL) return UNAVAILABLE;
    process_st *process = malloc(sizeof(process));
    if(process == NULL) return NOT_ENOUGH_MEMORY;
    process->pid = pid;
    process->status = ALIVE;
    if(set_process_name(process, name) == NOT_ENOUGH_MEMORY) return NOT_ENOUGH_MEMORY;
    size_t heap_size = calculate_heap_size(heap);
    process->heap.base = heap_size == EMPTY ? NULL : malloc(heap_size);
    process->heap.size = heap_size;
    processes[process->pid] = process;
    // to-do: calculate parent pid?
    thread_st *thread = create_thread(code, argv, stack, process->threads, process->pid);
    processes[process->pid]->threads[thread->tid] = thread;
    return process->pid;
}


