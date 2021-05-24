#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "circular_linked_list.h"
#include "../../task/include/process.h"

#define YES 1
#define START 0
#define BURST_TIME 3

#define MAX_PRIO 5


typedef struct {
    node_st *tail;
} rrnp_ts;

typedef void* heuristic;
typedef struct scheduler_s{
    size_t quantum;
    heuristic queue;
} scheduler_ts;


void queue_thread(thread_st *t, uint64_t priority);
scheduler_ts *init_no_prio_round_robin(size_t quantum);
void *schedule_handler(void *_rsp);
int get_current_pid();
void initialize_scheduler();
thread_st *get_current_thread();
void dequeue_current_process();

#endif