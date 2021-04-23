#include "include/process.h"

size_t process_count = 0;
process_st *processes[MAX_PROCESS_COUNT] = {NULL};

void kill_process(pid_t pid, size_t return_value) {
    if(pid > MAX_PROCESS_COUNT || pid <= 0 || processes[pid] == NULL) return;

    processes[pid]->status = KILLED;
    processes[pid]->return_value = return_value;
    _force_scheduler();
}

process_status_et get_process_state(pid_t pid) {
    return processes[pid]->status;
}
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

size_t set_process_name(process_st * process, char *name) {
    process->process_name = (char *) malloc(strnlen(name));
    if(process->process_name == NULL) return NOT_ENOUGH_MEMORY;
    my_strcpy(process->process_name, name);
    return SUCCESS;
}

void _start(function_t _main, size_t argc, char **argv) {
    int return_value = _main(argc, argv);
    kill_process(get_current_pid(), return_value);
}

size_t get_argv_count(char **argv) {
    size_t count = EMPTY;
    if(argv == NULL) return count;
    while(argv[count] != NULL) count++;
    return count;
}

pid_t create_process(char *name, address_t main, char **argv, size_t stack_size, size_t heap_size) {
    // to-do: erace pcb when stuff fails
    pid_t pid = get_available_pid();
    if(pid == UNAVAILABLE || main == NULL) return UNAVAILABLE;
    process_st *process = (process_st *) malloc(sizeof(process));
    if(process == NULL) return NOT_ENOUGH_MEMORY;
    process->pid = pid;
    process->status = READY;
    if(set_process_name(process, name) == NOT_ENOUGH_MEMORY) return NOT_ENOUGH_MEMORY;
    process->heap.base = heap_size == EMPTY ? NULL : (address_t) malloc(heap_size);
    process->heap.size = heap_size;
    processes[process->pid] = process;
    thread_st *thread = create_thread(main, argv, stack_size, process->threads, process->pid);
    if(thread == NULL) return NOT_ENOUGH_MEMORY;
    size_t argc = get_argv_count(argv);
    thread->stack.current = _stack_builder(&_start, main, (char *)thread->stack.base + stack_size, argc, argv);
    queue_thread(thread);
    processes[process->pid]->threads[thread->tid] = thread;
    process_count++;
    return process->pid;
}


void ps(ps_ts *process_info, int *p_count) {
    for(int i = 0; i < process_count; i++) {
        process_info[i].process_name = processes[i]->process_name;
        process_info[i].pid = processes[i]->pid;
        process_info[i].status = processes[i]->status;
        process_info[i].cs = processes[i]->threads[0]->stack.current;
        process_info[i].bp = processes[i]->threads[0]->stack.base;
    }
    *p_count = process_count;
}


