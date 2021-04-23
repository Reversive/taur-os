#ifndef UTILS_H
#define UTILS_H
typedef int pid_t;
typedef int tid_t;
typedef void* address_t;

typedef struct memory_block_t {
    address_t base;
    address_t current;
    size_t size;
} memory_block_st;

#endif