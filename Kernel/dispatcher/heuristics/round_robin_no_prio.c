#include "include/round_robin_no_prio.h"

thread_st *poll(scheduler_ts *scheduler) {
    rrnp_ts *queue = scheduler->queue;
    thread_st *head = get_head_data(queue->tail);
    queue->tail = queue->tail->next;
    return head;
}

thread_st *remove(scheduler_ts *scheduler, thread_st *thread) {
    return NULL;
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
    scheduler->add = add;
    scheduler->remove = remove;
    scheduler->poll = poll;
    return scheduler;
}