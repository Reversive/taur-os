#include "include/circular_linked_list.h"


node_st *create_node(void *data) {
    node_st *node = (node_st *)malloc(sizeof(node_st));
    node->data = data;
    return node;
}

int is_null(node_st *tail) {
    return tail == NULL;
}

int length(node_st *tail) {
    node_st *current_node = tail;
    if(is_null(current_node)) return 0;
    int length = 1;
    current_node = current_node->next;
    while(current_node != tail) {
        length++;
        current_node = current_node->next;
    }
    return length;
}

node_st *insert_head(node_st *tail, void *data) {
    node_st *node = (node_st *)malloc(sizeof(node_st));
    node->data = data;
    if(is_null(tail)) {
        tail = node;
        node->next = node;
    } else {
        node->next = tail->next;
        tail->next = node;
    }
    return tail;
}

node_st *insert_tail(node_st *tail, void *data) {
    return insert_head(tail, data)->next;
}

void *get_head_data(node_st *tail) {
    return is_null(tail) ? NULL : tail->next->data;
}

void *get_tail_data(node_st *tail) {
    return is_null(tail) ? NULL : tail->data;
}