// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/thread.h"

tid_t get_available_tid(thread_st **thread_list) {
    tid_t current_tid = UNAVAILABLE;
    for(int current_thread = 0; current_thread < MAX_THREAD_COUNT; current_thread++) {
        if(thread_list[current_thread] == NULL) current_tid = current_thread;
    }
    return current_tid;
}

void free_thread(thread_st *t) {
    free(t->stack.base);
    free(t);
}


thread_st *create_thread(address_t main, char **argv, size_t stack_size, thread_st **thread_list, pid_t pid) {
    if(stack_size == EMPTY) return NULL;
    tid_t tid = get_available_tid(thread_list);
    if(tid == UNAVAILABLE) return NULL;
    thread_st *thread = (thread_st *) malloc(sizeof(thread));
    if(thread == NULL) return NULL;
    thread->tid = tid;
    thread->pid = pid;
    thread->thread_status = RUNNING;
    thread->stack.base = (void*)((uint64_t)malloc(stack_size) + stack_size);
    if(thread->stack.base == NULL) {
        free_thread(thread);
        thread_list[MAIN_THREAD] = NULL;
        return NULL;
    }
    return thread;
}