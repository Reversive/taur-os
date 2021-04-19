#include "include/dummyMem.h"
#define TOTAL_MEM 1024      // 1024 es toda la memoria que va a administrar mi memory manager
#define BLOCK_SIZE 64

char start[TOTAL_MEM];      // start es el comienzo de la memoria para asignar

char *next = start;

// en vez de llamar un malloc, va a retornar un puntero a un slot libre de 64 bytes
void *my_dummy_malloc(unsigned int size){
	char *r = next;
	if(next - start < TOTAL_MEM - size) {   // la idea es que lo max que tengo es 1024 por start[1024]
        next +=size;
        return r;
    }
    else
	    return NULL;
}
	
