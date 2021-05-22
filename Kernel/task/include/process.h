#ifndef PROCESS_H
#define PROCESS_H

#include "thread.h"
#include "data_structures.h"
#include "../../include/lib.h"
#include <string.h>
#include "../../dispatcher/include/scheduler.h"

typedef int pid_t;

#ifndef INVALID_PID
#define INVALID_PID -1
#endif

#ifndef MAX_PROCESS_COUNT
#define MAX_PROCESS_COUNT 50
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef NOT_ENOUGH_MEMORY
#define NOT_ENOUGH_MEMORY -1
#endif

#ifndef STARTING_PRIO
#define STARTING_PRIO 5
#endif


extern process_st *processes[MAX_PROCESS_COUNT];
pid_t create_process(char *name, address_t main, char **argv, size_t stack_size, size_t heap_size, int prio);
pid_t get_available_pid();
int kill_process(pid_t pid, size_t return_value);
process_status_et get_process_state(pid_t pid);
void ps(ps_ts *process_info, int *p_count);
int set_process_niceness(pid_t pid, int priority);
pid_t set_process_state(pid_t pid, process_status_et status);
process_st *get_process_by_id(pid_t pid);
void free_process(pid_t pid);
#endif