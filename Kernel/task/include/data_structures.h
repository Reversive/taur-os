#ifndef UTILS_H
#define UTILS_H
typedef int pid_t;
typedef int tid_t;
typedef void* address_t;
#ifndef MAX_THREAD_COUNT
#define MAX_THREAD_COUNT 1
#endif
typedef enum { READY = 0, BLOCKED, KILLED } process_status_et;

typedef struct memory_block_t {
    address_t base;
    address_t current;
    size_t size;
} memory_block_st;

typedef enum { SUSPENDED = 0, RUNNING } thread_status_et;

typedef struct thread_t {
    tid_t tid;
    pid_t pid;
    thread_status_et thread_status;
    memory_block_st stack;
} thread_st;

typedef struct {
    pid_t pid;
    pid_t ppid;
    char *process_name;
    process_status_et status;
    memory_block_st heap;
    int return_value;
    thread_st *threads[MAX_THREAD_COUNT];
} process_st;

typedef struct {
    pid_t pid;
    char *process_name;
    address_t cs;
    address_t bp;
    process_status_et status;
} ps_ts;

typedef int (*function_t)(size_t argc, char **argv);


#endif