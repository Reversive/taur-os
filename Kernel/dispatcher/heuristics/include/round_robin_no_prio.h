#ifndef ROUND_ROBIN_NO_PRIO
#define ROUND_ROBIN_NO_PRIO
#include "circular_linked_list.h"
#include "../../include/scheduler.h"

typedef struct {
    node_st *tail;
} rrnp_ts;


scheduler_ts *init_no_prio_round_robin(size_t quantum);
#endif