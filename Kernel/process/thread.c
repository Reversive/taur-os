#include "include/thread.h"

tid_t get_available_tid(thread_st **thread_list) {
    tid_t current_tid = UNAVAILABLE;
    for(int current_thread = 0; current_thread < MAX_THREAD_COUNT; current_thread++) {
        if(thread_list[current_thread] == NULL) current_tid = current_thread;
    }
    return current_tid;
}

size_t calculate_stack_size(size_t size) {
    return size == EMPTY ? size : size * PAGE_SIZE;
}

thread_st *create_thread(address_t code, address_t *argv, size_t stack, thread_st **thread_list, pid_t pid) {
    if(stack == EMPTY) return NULL;
    tid_t tid = get_available_tid(thread_list);
    if(tid == UNAVAILABLE) return NULL;
    thread_st *thread = malloc(sizeof(thread));
    if(thread == NULL) return NULL;
    thread->tid = tid;
    thread->pid = pid;
    thread->status = RUNNING;
    size_t stack_size = calculate_stack_size(stack);
    thread->stack.base = stack_size == EMPTY ? NULL : malloc(stack_size);
    // TO-DO: queue thread
    return thread;
}