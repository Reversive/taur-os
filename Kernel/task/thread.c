#include "include/thread.h"

tid_t get_available_tid(thread_st **thread_list) {
    tid_t current_tid = UNAVAILABLE;
    for(int current_thread = 0; current_thread < MAX_THREAD_COUNT; current_thread++) {
        if(thread_list[current_thread] == NULL) current_tid = current_thread;
    }
    return current_tid;
}


size_t get_argv_count(char **argv) {
    size_t count = EMPTY;
    if(argv == NULL) return count;
    while(argv[count] != NULL) count++;
    return count;
}

void _start(function_t _main, size_t argc, char **argv) {
    int return_value = _main(argc, argv);
    kill_process(get_current_pid(), return_value);
}

thread_st *create_thread(address_t main, char **argv, size_t stack_size, thread_st **thread_list, pid_t pid) {
    if(stack_size == EMPTY) return NULL;
    tid_t tid = get_available_tid(thread_list);
    if(tid == UNAVAILABLE) return NULL;
    thread_st *thread = (thread_st *) malloc(sizeof(thread));
    if(thread == NULL) return NULL;
    thread->tid = tid;
    thread->pid = pid;
    thread->status = RUNNING;
    thread->stack.base = stack_size == EMPTY ? NULL : malloc(stack_size);
    if(thread->stack.base == NULL) return NULL;
    size_t argc = get_argv_count(argv);
    thread->stack.current = _stack_builder(&_start, main, (char *)thread->stack.base + stack_size, argv, argc);
    queue_thread(thread);
    return thread;
}