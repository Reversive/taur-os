// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* Based on FreeRTOS Kernel V10.4.3
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS */

#include "include/buddy.h"
#include "../drivers/shell/include/shell.h"

typedef struct Header {
    struct Header * next;
    size_t size;
    char side[30] ;
} header;
// SIDE: 0=left, 1=right

/* Inserts a block of memory to the list of free mem blocks.
 * Merges adjacent free zones into one. */
static void add_block_to_free_list(header * blockToInsert);

/* Sets up the required heap on the first call to malloc */
static void init_heap();

/* The size of the structure placed at the beginning of each allocated
 *  memory block must be correctly byte aligned. */
//static const size_t heap_construct_size = (sizeof(header) + ((size_t) (BYTE_ALIGNMENT - 1))) & ~((size_t) BYTE_ALIGNMENT_MASK);

/* Block sizes must not get too small. */
//#define heapMINIMUM_BLOCK_SIZE ((size_t) (heap_construct_size << 1 ))

/* Links to the free list*/
static header start, * pEnd = NULL;

static size_t free_bytes_remaining = 0;

/* Total memory heap*/
// uint8_t tot_mem[TOTAL_HEAP_SIZE];
void * tot_mem;


/* Gets set to the top bit of an size_t type.  When this bit in the size
 * member of an header structure is set then the block belongs to the
 * application.  When the bit is free the block is still part of the free heap
 * space. */
static size_t xBlockAllocatedBit = 0;
void printList(int num){
    header *iteratorp;
    iteratorp = &start;
    _internal_print_string("LOOK AT FREE LIST ");
    _internal_print_dec(num);
    print_char('\n');
    while(iteratorp->next !=NULL){
        iteratorp = iteratorp->next;
        _internal_print_dec(iteratorp->size);
        print_char('\n');
    }
}

void * malloc(size_t requestedSize) {
    _internal_print_string("in malloc\n requested size");
    _internal_print_dec(requestedSize);
    print_char('\n');
    header * currp,* prevp, *insertp, * minp, * minprevp;
    void * returnp = NULL;

    if(pEnd == NULL){
        init_heap();
    }

    /* Checks that the requested block doesn't set the top bit
     * The top bit determines if the block is free or not. */
    if((requestedSize & xBlockAllocatedBit) == 0) {
        /* We have free space for the requested size */
        if((requestedSize > 0) && ( requestedSize <= free_bytes_remaining)) {
            /* Traverse the list from the start	(lowest address) block until
            * one of adequate size is found. */
            prevp = &start;
            currp = start.next;
            minp = NULL; 
            minprevp = &start;

            while((currp != NULL)) {
                print_char('\n');
                print_char('\n');
                _internal_print_string("in while getting minp\n");
                _internal_print_dec(currp->size);
                print_char('\n');
                _internal_print_string("requested size = ");
                _internal_print_dec(requestedSize);
                print_char('\n');


                if((minp->size > currp->size || minp == NULL) && currp->size >= requestedSize){
                    minprevp = prevp;
                    minp = currp;
                    if(minprevp->next->size != minp->size){
                        while(1)
                            _internal_print_string("there has been an error\n");
                    }
                }
                prevp = currp;
                currp = currp->next;

                print_char('\n');
                print_char('\n');
                print_char('\n');
                print_char('\n');
            }

            /* If the end marker was reached then a block of adequate size
             * was not found. */
            _internal_print_string("got minp\n");
            currp = minp;
            prevp = minprevp;
            _internal_print_dec(currp->size);
            print_char('\n');
            if(currp != NULL) {
                /* Return the memory space pointed to - jumping over the
                 * header structure at its start. */
                //returnp = (void *) (((uint8_t *) prevp->next) + heap_construct_size);
                returnp = (void *) (((uint8_t *) prevp->next) );


                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                prevp->next = currp->next;
                /* If the block is larger than required it can be split into two. */
                    
                while((currp->size/2)>=requestedSize){
                    _internal_print_string("estamos en ");
                    _internal_print_dec(currp->size);
                    _internal_print_string(" queremos ir a ");
                    _internal_print_dec(currp->size/2);
                    print_char('\n');
                    _internal_print_string(currp->side);
                    print_char('\n');
                    header * prightBlock;
                    size_t sizes = ((currp->size)/2);
                    header * iteratorp;
                    prightBlock  = (void *) (((uint8_t *) currp) + sizes);
                    
                    
                    prightBlock->size = sizes;
                    
                    currp->size = sizes;
                    iteratorp = &start;
                    int i = 0;
                    while(currp->side[i]!=0){
                        printList(0);
                        prightBlock->side[i] = currp->side[i];
                        printList(1);
                        i++;
                    }
                    currp->side[i] = 'l';
                    prightBlock->side[i] = 'r';
                    add_block_to_free_list(prightBlock);
                }

                free_bytes_remaining -= currp->size;

                /* The block is being returned - it is allocated and owned
                 * by the application and has no "next" block. */
                currp->size |= xBlockAllocatedBit;
                currp->next = NULL;
            }else{
                while(1)
                    _internal_print_string("couldnt find!\n");
            }
        }
    }
    
    return returnp;
}


int myPow(int base, int power) {
    int result = 1;
    int i;
    for(i=0; i<power; i++) {
        result *= base;
    }
    return result;
}

int biggestBuddy() {
    _internal_print_string("biggest buddy\n");
    int i = 0;
    unsigned int totalHeap = 1;
    while(myPow(2,i) < TOTAL_HEAP_SIZE){
        totalHeap *=2; 
        i++;
    }
    _internal_print_dec(totalHeap);
    print_char('\n');
    return totalHeap;

}

static void init_heap() {
    _internal_print_string("init heap");
    print_char('\n');
    header * pFirstFreeBlock;
    uint8_t * pAlignedHeap;
    size_t totalMemPointer;
    size_t totalHeapSize = biggestBuddy();

    sbrk_handler(totalHeapSize, &tot_mem);

    /* Ensure the heap starts on a correctly aligned boundary. */
    totalMemPointer = (size_t) tot_mem;

    pAlignedHeap = (uint8_t *) totalMemPointer;

    /* start is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    start.next = (void *) pAlignedHeap;
    start.size = (size_t) 0;

    /* pEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    pEnd = (void *) totalMemPointer;

    /* To start, there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pEnd. */
    pFirstFreeBlock = (void *) pAlignedHeap;
    pFirstFreeBlock->size = totalHeapSize;
    pFirstFreeBlock->next = NULL;
    pFirstFreeBlock->side[0] = 'l';

    /* Only one block exists - and it covers the entire usable heap space. */
    free_bytes_remaining = pFirstFreeBlock->size;
    /* Work out the position of the top bit in a size_t variable. */
    xBlockAllocatedBit = ((size_t) 1) << ((sizeof(size_t) * heapBITS_PER_BYTE) - 1);
}



void free(void *ptr){

    uint8_t * currp = (uint8_t *) ptr;
    header * insertp;

    if(ptr != NULL) {
        /* The memory being freed will have a header structure immediately before it. */
        //currp -= heap_construct_size;

        /* This casting is to keep the compiler from issuing warnings. */
        insertp = (void *) currp;

        if((insertp->size & xBlockAllocatedBit) != 0) {
            if(insertp->next == NULL) {
                /* The block is being returned to the heap - it is no longer allocated. */
                insertp->size &= ~xBlockAllocatedBit;
                
                /* Add this block to the list of free blocks. */
                free_bytes_remaining += insertp->size;
                // traceFREE( ptr, insertp->size );
                add_block_to_free_list(((header *) insertp));
            }
        }
    }
}



static void add_block_to_free_list(header * blockToInsert) {
    _internal_print_string("ADD BLOCK TO FREE LIST\n");
    header * iteratorp;
    uint8_t * currp;
    
    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    
    iteratorp = &start;
    if(iteratorp->next == NULL){
        _internal_print_string("free list empty\n");
        start.next =  blockToInsert;
        blockToInsert->next = NULL;
       
        return;
    }
    while(iteratorp->next < blockToInsert || iteratorp->next == NULL) {
        iteratorp = iteratorp->next;
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    currp = (uint8_t *) iteratorp;
    // unir del lado izquierdo 
    int i=0;
    while(blockToInsert->side[i] != 0){
        i++;
    }
    int j=0;
    while(iteratorp->side[j] != 0){
        j++;
    }

    if(((currp + iteratorp->size) == (uint8_t *) blockToInsert) && blockToInsert->side[i-1] == 'r' && iteratorp->side[j-1] == 'l'&& j==i) {
        _internal_print_string("im gonna join left\n");
        iteratorp->size += blockToInsert->size;
        iteratorp->side[j-1] = 0;
        j--;
        i--;
        blockToInsert = iteratorp;
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    currp = (uint8_t *) blockToInsert;
    j=0;
    while(iteratorp->next->side[j] != 0){
        j++;
    }
    // unir por derecha
    if(((currp + blockToInsert->size) == (uint8_t *) iteratorp->next) && blockToInsert->side[i-1] == 'l' && iteratorp->next->side[j-1] == 'r'&& j==i) {
        _internal_print_string("im gonna join right\n");
        //if(iteratorp->next != pEnd) {
        if(iteratorp->next != NULL) {
            /* Form one big block from the two blocks. */
            blockToInsert->size += iteratorp->next->size;
            blockToInsert->next = iteratorp->next->next;
            blockToInsert->side[i-1] = 0;
        } else {
            //blockToInsert->next = pEnd;
            blockToInsert->next = NULL;
        }
    } else {
        _internal_print_string("yey else\n");
        blockToInsert->next = iteratorp->next;
    }

    /* If the block being inserted plugged a gab, so was merged with the block
     * before and the block after, then it's next pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    if(iteratorp != blockToInsert) {
        _internal_print_string("fim in if\n");
        iteratorp->next = blockToInsert;
    }
    
}