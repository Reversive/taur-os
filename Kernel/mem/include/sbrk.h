#ifndef SBRK_H
#define SBRK_H
    
    #include <stdint.h>
    #include <stdlib.h>

    //  increments the end of DataSeg and return the beginning of the allocked space 
    void sbrkHandler(int increment, void ** buffer);

#endif