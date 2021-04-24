#include "include/scheduler.h"
thread_st * current_thread;
scheduler_ts *scheduler;
size_t current_quantum = START;
int first_appearence = YES;

thread_st *get_current_thread() {
    return current_thread;
}

thread_st *poll(scheduler_ts *scheduler) {
    rrnp_ts *queue = scheduler->queue;
    thread_st *head = get_head_data(queue->tail);
    queue->tail = queue->tail->next;
    return head;
}

thread_st *remove(scheduler_ts *scheduler, thread_st *thread) {
    return NULL; // to-do
}

void add(scheduler_ts *scheduler, thread_st *thread) {
    rrnp_ts *queue = scheduler->queue;
    queue->tail = insert_tail(queue->tail, thread);
}

scheduler_ts *init_no_prio_round_robin(size_t quantum) {
    scheduler_ts *scheduler = malloc(sizeof(scheduler_ts));
    rrnp_ts *queue = malloc(sizeof(node_st));
    scheduler->quantum = quantum;
    scheduler->queue = queue;
    return scheduler;
}

int get_current_pid() {
    return current_thread->pid;
}

void initialize_scheduler() {
    current_thread = NULL;
    scheduler = init_no_prio_round_robin(BURST_TIME);
}

void queue_thread(thread_st *t) {
    add(scheduler, t);
}

void *schedule_handler(void *_rsp) {
    if(current_thread == NULL) current_thread = poll(scheduler);

    if(first_appearence) {
        first_appearence = !first_appearence;
        return current_thread->stack.current;
    }

   if(current_quantum < scheduler->quantum) {
        current_thread->stack.current = _rsp;
        current_quantum++;
    } else {
        current_thread->stack.current = _rsp;
        current_thread = poll(scheduler);
        while(get_process_state(current_thread->pid) != READY) current_thread = poll(scheduler);
        current_quantum = START;
    }

    return current_thread->stack.current;
}