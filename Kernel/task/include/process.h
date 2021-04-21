#ifndef PROCESS_H
#define PROCESS_H

#include "thread.h"
#include "../../include/lib.h"
#include <string.h>


#ifndef MAX_PROCESS_COUNT
#define MAX_PROCESS_COUNT 5
#endif


#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef NOT_ENOUGH_MEMORY
#define NOT_ENOUGH_MEMORY -1
#endif

typedef enum { ZOMBIE = 0, ALIVE } process_status_et;

typedef struct {
    pid_t pid;
    pid_t ppid;
    char *process_name;
    process_status_et status;
    memory_block_st heap;
    thread_st *threads[MAX_THREAD_COUNT]; // We only have 1 main thread but we keep this for scalability
} process_st;

extern process_st *processes[MAX_PROCESS_COUNT];

pid_t create_process(char *name, address_t code, char **argv, size_t stack, size_t heap);
pid_t get_available_pid();

#endif