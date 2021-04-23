#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "../../task/include/thread.h"
#include "../heuristics/include/circular_linked_list.h"
#include "../../drivers/shell/include/shell.h"
typedef void* heuristic;
#define START 0
typedef struct thread_t thread_st;
typedef struct scheduler_s{
    size_t quantum;
    void (*add)(struct scheduler_s *scheduler, thread_st *thread);
    thread_st *(*remove)(struct scheduler_s *scheduler, thread_st *thread);
    thread_st *(*poll)(struct scheduler_s *scheduler);
    heuristic queue;
} scheduler_ts;

#include "../heuristics/include/round_robin_no_prio.h"

void queue_thread(thread_st *t);
void *schedule_handler(void *_rsp);
int get_current_pid();
void initialize_scheduler();
#endif