// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
    node_st *node = create_node(data);
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

node_st *delete_by_value(node_st *tail, void *data, comparator cmp, fdata free_data) {
    node_st *current = tail, *previous;
    if (tail == NULL)
        return tail;
    else if (tail == tail->next) {
        if (cmp(tail->data, data) == 0) {
            tail = NULL;
            free_data(current->data);
            free(current);
        }
    }
    do {
        previous = current;
        current = current->next;
        if (cmp(current->data, data) == 0) {
            previous->next = current->next;
            if (current == tail) tail = previous;
            free_data(current->data);
            free(current);
        }
    } while (current != tail);
    return tail;
}

void *get_head_data(node_st *tail) {
    return is_null(tail) ? NULL : tail->next->data;
}

void *get_tail_data(node_st *tail) {
    return is_null(tail) ? NULL : tail->data;
}

node_st *delete_by_location(node_st *tail, int location) {
    node_st *current = tail, *previous = tail;
    int len = length(tail), i;
    if (location < 1 || location > len) {
        return tail;
    } else if (len == 1) {
        tail = NULL;
        free(current);
    } else {
        current = tail->next;
        for (i = 1; i < location; i++) {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
        if (current == tail) tail = previous;
        free(current);
    }
    return tail;
}

node_st *delete_head(node_st *tail) {
    return delete_by_location(tail, 1);
}