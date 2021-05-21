#ifndef _MM_H
#define _MM_H

    #include <string.h>
    #include <stdint.h>
    #include "sbrk.h"

    #define BASE 2
    #define GIGA 30
    #define MIN_ALLOC_LOG2 6                            // Min size = 64 bytes
    #define MAX_ALLOC_LOG2 (GIGA - MIN_ALLOC_LOG2)      // Max size = 1 GB
    #define BINARY_POWER(x) (1 << (x))
    #define TOTAL_HEAP_SIZE (1024 * 500)

    #ifndef NULL
        #define NULL 0
    #endif
    
    typedef enum { false, true } bool;

    void free(void *ptr);
    void *malloc(size_t requestedSize);

#endif