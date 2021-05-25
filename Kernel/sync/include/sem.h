#ifndef SEM_H
#define SEM_H

#include "../../include/lib.h"
#include "../../task/include/process.h"
#include "../../dispatcher/include/scheduler.h"
#include <stdint.h>

#define MAX_PROC 50
#define MAX_SEMS 256
#define NAME_CHAR_LIMIT 1024
#define OUT_OF_BOUNDS -1
#define ERROR -1

typedef struct {
    int sem_id;
    char name[NAME_CHAR_LIMIT];
    uint64_t lock;   // lock
    uint64_t value;
    uint64_t open_count;    // Counter of pending 'close' signals
    uint64_t blocked_processes[MAX_PROC];
    uint64_t blocked_first;
    uint64_t blocked_last;
} sem_ts;

typedef sem_ts *p_sem;

int sem_open(char *name, int value);
int	sem_wait(char *name);
int sem_post(char *name);
int sem_close(char *name);
int get_sem_count();
int get_sem_info(int idx, p_sem buffer);

#endif