#ifndef _MM_H
#define _MM_H

    // #include <stdio.h>
    #include <string.h>
    #include <stdint.h>
    #include "sbrk.h"

    #ifndef NULL
        #define NULL 0
    #endif

    void free(void *ptr);
    void *malloc(size_t requestedSize);

#endif