#ifndef UTILS_H
#define UTILS_H
typedef int pid_t;
typedef int tid_t;
typedef void* address_t;
#ifndef MAX_THREAD_COUNT
#define MAX_THREAD_COUNT 1
#endif
typedef enum { READY = 0, BLOCKED, KILLED, INVALID } process_status_et;

typedef struct memory_block_t {
    address_t base;
    address_t current;
    address_t start;
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
    int priority;
    int foreground;
    thread_st *threads[MAX_THREAD_COUNT];
} process_st;

typedef struct {
    pid_t pid;
    char *process_name;
    int foreground;
    int priority;
    address_t cs;
    address_t bp;
    process_status_et status;
} ps_ts;

#define MAXPIPES 10
#define PIPESIZE 1000
#define PROCESSES 10
#define MAX_NAM 100
typedef struct {
    char name[MAX_NAM];
    int created;
    char data[PIPESIZE];
    int rProcesses[PROCESSES];
    int wProcesses[PROCESSES];
    unsigned int nread;
    unsigned int nwrite;
    int usingPipe;
    int waitingPid;
    int fd;
}pipe_t;
typedef int (*function_t)(size_t argc, char **argv);


#endif