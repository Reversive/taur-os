#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H
#include "../../mem/include/mm.h"

#ifndef EMPTY
#define EMPTY 0
#endif

typedef struct node_s {
    void *data;
    struct node_s *next;
} node_st;



#endif