#include "include/memory_manager.h"
#define TOTAL_MEM 4096  
#define BLOCK_SIZE 64

char start[TOTAL_MEM];    

char *next = start;

void *malloc(unsigned int size){
	char *r = next;
	if(next - start < TOTAL_MEM - size) {   
        next +=size;
        return r;
    }
    else
	    return NULL;
}