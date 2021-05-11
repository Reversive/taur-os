#ifndef _MM_H
#define _MM_H

    // #include <stdio.h>
    #include <string.h>
    #include <stdint.h>
    #include "sbrk.h"

    #define BYTE_ALIGNMENT 64
    #define BYTE_ALIGNMENT_MASK ( 0x003f )
    #define TOTAL_HEAP_SIZE ((size_t) 1024 * 500)
    #define heapBITS_PER_BYTE ((size_t) 8)

    #ifndef NULL
        #define NULL 0
    #endif

    // typedef unsigned int size_t;

    void myFree(void *ptr);
    void *myMalloc(size_t requestedSize);

#endif