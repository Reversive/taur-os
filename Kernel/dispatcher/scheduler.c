// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/scheduler.h"
#include "../task/include/process.h"

thread_st * current_thread;
scheduler_ts *scheduler;
size_t current_quantum = START;
int first_appearence = YES;
uint64_t disable_count = 0;
pid_t foreground_pid = START;

int cmp(void * p1, void * p2) {
    return !(p1 == p2);
}

thread_st *get_current_thread() {
    return current_thread;
}

thread_st *rrnp_poll(scheduler_ts *scheduler) {
    rrnp_ts *queue = scheduler->queue;
    thread_st *head = get_head_data(queue->tail);
    queue->tail = queue->tail->next;
    return head;
}

void free_data(void *data) {
    free_thread((thread_st *)data);
}

void rrnp_remove(scheduler_ts *scheduler, thread_st *thread) {
    rrnp_ts *queue = scheduler->queue;
    free_process(thread->pid);
    queue->tail = delete_by_value(queue->tail, thread, cmp, free_data);
}

void rrnp_add(scheduler_ts *scheduler, thread_st *thread) {
    rrnp_ts *queue = scheduler->queue;
    queue->tail = insert_tail(queue->tail, thread);
}

void dequeue_current_process() {
    rrnp_remove(scheduler, current_thread);
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

int get_foreground_pid() {
    return foreground_pid;
}

void initialize_scheduler() {
    current_thread = NULL;
    scheduler = init_no_prio_round_robin(BURST_TIME);
}

void queue_thread(thread_st *t, uint64_t priority) {
    rrnp_add(scheduler, t);
}

void scheduler_enable() {
    if(disable_count > 0)
        disable_count--;
}

void scheduler_disable() {
    int count;
    do count = disable_count; 
    while(_cmpxchg(&disable_count, count+1, count) != count);
}

void *schedule_handler(void *_rsp) {
    if(disable_count) {
        return current_thread->stack.current = _rsp;
    }

    if(current_thread == NULL)
        current_thread = rrnp_poll(scheduler);

    if(first_appearence) {
        first_appearence = !first_appearence;
        return current_thread->stack.current;
    }

    
    process_st *p = get_process_by_id(current_thread->pid);
    if(p->foreground) foreground_pid = p->pid;

    if(p->status == KILLED) {
        rrnp_remove(scheduler, current_thread);
        current_thread = rrnp_poll(scheduler);
        while(get_process_state(current_thread->pid) != READY) current_thread = rrnp_poll(scheduler);
        current_quantum = START;
    } else {
        if(current_quantum < p->priority && !is_forcing) {
            current_thread->stack.current = _rsp;
            current_quantum++;
        } else {
            if(is_forcing) is_forcing = 0;
            current_thread->stack.current = _rsp;
            current_thread = rrnp_poll(scheduler);
            process_status_et status = get_process_state(current_thread->pid);
            while(status != READY) {
                if(status == KILLED) {
                    rrnp_remove(scheduler, current_thread);
                }
                current_thread = rrnp_poll(scheduler);
                status = get_process_state(current_thread->pid);
            }
            current_quantum = START;
        }
    }

    return current_thread->stack.current;
}