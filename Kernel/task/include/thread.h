#ifndef THREAD_H
#define THREAD_H
#include "../../mem/include/mm.h"
#include "../../asm/include/libasm.h"
#include "../../drivers/shell/include/shell.h"
#include "../../dispatcher/include/scheduler.h"
#include "utils.h"



#ifndef EMPTY
#define EMPTY 0
#endif

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

#ifndef MIN_PAGE_AMOUNT
#define MIN_PAGE_AMOUNT 4
#endif

#ifndef UNAVAILABLE
#define UNAVAILABLE -1
#endif


typedef enum { SUSPENDED = 0, RUNNING } thread_status_et;

typedef struct thread_t {
    tid_t tid;
    pid_t pid;
    thread_status_et status;
    memory_block_st stack;
} thread_st;

#include "process.h"

typedef int (*function_t)(size_t argc, char **argv);

thread_st *create_thread(address_t code, char **argv, size_t stack, thread_st **thread_list, pid_t pid);
size_t calculate_stack_size(size_t size);
tid_t get_available_tid(thread_st **thread_list);
size_t get_argv_count(char **argv);

#endif