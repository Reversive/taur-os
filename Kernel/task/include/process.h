#ifndef PROCESS_H
#define PROCESS_H

#include "thread.h"
#include "../../include/lib.h"
#include <string.h>

typedef int pid_t;

#ifndef MAX_PROCESS_COUNT
#define MAX_PROCESS_COUNT 5
#endif


#ifndef MAX_THREAD_COUNT
#define MAX_THREAD_COUNT 1
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef NOT_ENOUGH_MEMORY
#define NOT_ENOUGH_MEMORY -1
#endif

typedef enum { READY = 0, BLOCKED, KILLED } process_status_et;


typedef struct {
    pid_t pid;
    pid_t ppid;
    char *process_name;
    process_status_et status;
    memory_block_st heap;
    int return_value;
    thread_st *threads[MAX_THREAD_COUNT]; // = 1
} process_st;

extern process_st *processes[MAX_PROCESS_COUNT];

pid_t create_process(char *name, address_t code, char **argv, size_t stack, size_t heap);
pid_t get_available_pid();
void kill_process(int pid, int return_value);

#endif