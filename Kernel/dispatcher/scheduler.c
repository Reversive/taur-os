#include "include/scheduler.h"
thread_st * current_thread;
scheduler_ts *scheduler;
size_t current_quantum = START;

int get_current_pid() {
    return current_thread->pid;
}

void initialize_scheduler() {
    current_thread = NULL;
    scheduler = init_no_prio_round_robin(4);
}

void queue_thread(thread_st *t) {
    scheduler->add(scheduler, t);
}

int first_appearence = 1;
void *schedule_handler(void *_rsp) {
    if(current_thread == NULL) current_thread = scheduler->poll(scheduler);

    if(first_appearence) {
        first_appearence = !first_appearence;
        return current_thread->stack.current;
    }

   if(current_quantum < scheduler->quantum) {
        current_thread->stack.current = _rsp;
        current_quantum++;
    } else {
        current_thread->stack.current = _rsp;
        current_thread = scheduler->poll(scheduler);
        current_quantum = START;
    }

    return current_thread->stack.current;
}