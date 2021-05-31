#include "include/shmem.h"

#define CANT_KEYS 5
#define SIZE 4096
#define NOT_ENOUGH_MEMORY NULL

uint64_t *shm[CANT_KEYS] = {NULL};

void * malloc_shmem(int key) {
    if(shm[key] == NULL) {
        void *p = malloc(SIZE);
        if(p == NULL) return NOT_ENOUGH_MEMORY;
        shm[key] = (uint64_t*)p;
    }
    return shm[key];
}

void free_shmem(int key){
    free(shm[key]);
}


