#ifndef THREAD_H
#define THREAD_H
#include "../../memory/include/memory_manager.h"

typedef int pid_t;
typedef int tid_t;
typedef int size_t;
typedef void* address_t;

#ifndef EMPTY
#define EMPTY 0
#endif

#ifndef PAGE_SIZE
#define PAGE_SIZE 4
#endif

#ifndef UNAVAILABLE
#define UNAVAILABLE -1
#endif

#ifndef MAX_THREAD_COUNT
#define MAX_THREAD_COUNT 3
#endif

typedef enum { SUSPENDED = 0, RUNNING } thread_status_et;

typedef struct {
    address_t base;
    size_t size;
} memory_block_st;

typedef struct {
    tid_t tid;
    pid_t pid;
    thread_status_et status;
    memory_block_st stack;
} thread_st;

thread_st *create_thread(address_t code, address_t *argv, size_t stack, thread_st **thread_list, pid_t pid);
size_t calculate_stack_size(size_t size);
tid_t get_available_tid(thread_st **thread_list);
#endif