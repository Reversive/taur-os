#ifndef PROCESS_H
#define PROCESS_H

#include "thread.h"
#include "data_structures.h"
#include "../../include/lib.h"
#include <string.h>
#include "../../dispatcher/include/scheduler.h"

typedef int pid_t;

#ifndef MAX_PROCESS_COUNT
#define MAX_PROCESS_COUNT 25
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef NOT_ENOUGH_MEMORY
#define NOT_ENOUGH_MEMORY -1
#endif


extern process_st *processes[MAX_PROCESS_COUNT];

pid_t create_process(char *name, address_t code, char **argv, size_t stack, size_t heap);
pid_t get_available_pid();
void kill_process(pid_t pid, size_t return_value);
process_status_et get_process_state(pid_t pid);
void ps(ps_ts *process_info, int *p_count);
#endif