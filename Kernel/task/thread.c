// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/thread.h"


void free_thread(thread_st *t) {
    free(t->stack.start);
    free(t);
}


thread_st *create_thread(address_t main, char **argv, size_t stack_size, thread_st **thread_list, pid_t pid) {
    if(stack_size == EMPTY) return NULL;
    tid_t tid = MAIN_THREAD;
    thread_st *thread = (thread_st *) malloc(sizeof(thread));
    if(thread == NULL) return NULL;
    thread->tid = tid;
    thread->pid = pid;
    thread->thread_status = RUNNING;
    thread->stack.start = (address_t)malloc(stack_size);
    thread->stack.base = (void*)((uint64_t)thread->stack.start + stack_size);
    if(thread->stack.start == NULL) {
        free_thread(thread);
        thread_list[MAIN_THREAD] = NULL;
        return NULL;
    }
    return thread;
}