#ifndef _MM_H
#define _MM_H

    // #include <stdio.h>
    #include <string.h>
    #include <stdint.h>
    #include "sbrk.h"

    #ifndef NULL
        #define NULL 0
    #endif

    void myFree(void *ptr);
    void *myMalloc(size_t requestedSize);

#endif