#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H
#include "../../mem/include/mm.h"
#include "../../mem/include/buddy.h"
#ifndef EMPTY
#define EMPTY 0
#endif

typedef struct node_s {
    void *data;
    struct node_s *next;
} node_st;

typedef int (*comparator)(void *, void *);
typedef void (*fdata)(void *);

node_st *create_node(void *data);

int is_null(node_st *tail);

int length(node_st *tail);

node_st *insert_head(node_st *tail, void *data);

node_st *insert_tail(node_st *tail, void *data);

void *get_head_data(node_st *tail);

node_st *delete_by_value(node_st *tail, void *data, comparator cmp, fdata free_data);



#endif