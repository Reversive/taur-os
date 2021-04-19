#ifndef MM_H
#define MM_H

    #include <stdio.h>
    #include <lib.h>
    #include <stdint.h>

    #define BYTE_ALIGNMENT 64
    #define BYTE_ALIGNMENT_MASK ( 0x003f )
    #define TOTAL_HEAP_SIZE ((size_t) 10 * 1024)
    #define heapBITS_PER_BYTE ((size_t) 8)

    void myFree(void *ptr);
    void * myMalloc(size_t requestedSize);

#endif