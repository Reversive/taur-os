// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/scheduler.h"
thread_st * current_thread;
scheduler_ts *scheduler;
size_t current_quantum = START;
int first_appearence = YES;

thread_st *get_current_thread() {
    return current_thread;
}

thread_st *rrnp_poll(scheduler_ts *scheduler) {
    rrnp_ts *queue = scheduler->queue;
    thread_st *head = get_head_data(queue->tail);
    queue->tail = queue->tail->next;
    return head;
}

thread_st *rrnp_remove(scheduler_ts *scheduler, thread_st *thread) {
    return NULL; // to-do
}

void rrnp_add(scheduler_ts *scheduler, thread_st *thread) {
    rrnp_ts *queue = scheduler->queue;
    queue->tail = insert_tail(queue->tail, thread);
}

scheduler_ts *init_no_prio_round_robin(size_t quantum) {
    scheduler_ts *sch = malloc(sizeof(scheduler_ts));
    if(sch == NULL) return NULL;
    rrnp_ts *queue = malloc(sizeof(rrnp_ts));
    if(queue == NULL) {
        free(sch);
        return NULL;
    }
    sch->quantum = quantum;
    sch->queue = queue;
    return sch;
}

int get_current_pid() {
    return current_thread->pid;
}

void initialize_scheduler() {
    current_thread = NULL;
    scheduler = init_no_prio_round_robin(BURST_TIME);
}

void queue_thread(thread_st *t, uint64_t priority) {
    rrnp_add(scheduler, t);
}


void *schedule_handler(void *_rsp) {
    if(current_thread == NULL) current_thread = rrnp_poll(scheduler);

    if(first_appearence) {
        first_appearence = !first_appearence;
        return current_thread->stack.current;
    }
    
   if(current_quantum < get_process_by_id(current_thread->pid)->priority) {
        current_thread->stack.current = _rsp;
        current_quantum++;
    } else {
        current_thread->stack.current = _rsp;
        current_thread = rrnp_poll(scheduler);
        while(get_process_state(current_thread->pid) != READY) current_thread = rrnp_poll(scheduler);
        current_quantum = START;
    }

    return current_thread->stack.current;
}