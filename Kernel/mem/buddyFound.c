#include <string.h>
#include <stdint.h>
#include "./include/sbrk.h"  
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/mman.h>
// #include <string.h>
// #include <stdint.h>
// #include <assert.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

// function declarations
void *malloc(size_t);
void free(void *);
void dump_memory_map(void);
void offset_updater(int *, int);
int *tom_brady(int *);
int *gronk(int *, int);
void free_offset_updater(int *);
//const int HEAPSIZE = (1024); // 1 MB
const int HEAPSIZE = (1*1024*1024); // 1 MB
const int MINIMUM_ALLOC = sizeof(int) * 2;

// global file-scope variables for keeping track
// of the beginning of the heap.
void *heap_begin = NULL;
int *free_list = NULL;

/*
the gronk function is the work horse of malloc, performing all of the 
recursive work of splitting free blocks into chunks of the correct size, 
hence the namesake gronk
all honor to his name
*/
int *gronk(int *heap_pointer,  int alloc_size)
{
    int *heap_ptr = heap_pointer;
            
    if (heap_ptr[0] == alloc_size) //heap_ptr points to a block of the correct size
    { 
        if(heap_ptr == free_list) //if this block is the first free block
        {
            free_list += heap_ptr[1]/4; //update freelist to point to next free block
        }
        int old_offset = heap_ptr[1]; //save the old offset
        heap_ptr[1] = 0;  //mark as allocated
        offset_updater(heap_ptr, old_offset);
        return heap_ptr + 2;
    }

    if (heap_ptr[0] < alloc_size) //heap_ptr point to block that is too small
    {
        if (heap_ptr[1] == 0) //if this is the last free block
            return NULL;
        int ptr_offset = heap_ptr[1]/4;
        return gronk(heap_ptr + ptr_offset, alloc_size);
                                                            
    } else {
        int buddy = heap_ptr[0]/2;  //buddy = size of block/2
        int old_offset = heap_ptr[1]; //save the old offset
        heap_ptr[0] = buddy; //set the size of the current block
        heap_ptr[1] = buddy; //set the offset to point to the buddy
        int buddy_offset = buddy/4;
        heap_ptr[buddy_offset] = buddy; //set size of buddy block
        if(old_offset == 0) 
            heap_ptr[buddy_offset + 1] = 0;
        else                      
            heap_ptr[buddy_offset + 1] = old_offset - buddy;
        return gronk(heap_ptr, alloc_size);
    }
}

void *malloc(size_t request_size)
{
    int *alloc_ptr;
    // if heap_begin is NULL, then this must be the first
    // time that malloc has been called.  ask for a new
    // heap segment from the OS using mmap and initialize
    // the heap begin pointer.   
    if (!heap_begin)
    {
        // heap_begin = mmap(NULL, HEAPSIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
        
        
        sbrk_handler(HEAPSIZE, &heap_begin);
        //atexit(dump_memory_map);
        //initialize first header
        free_list = heap_begin;
        free_list[0] = HEAPSIZE;
        free_list[1] = 0; //0 for last free block
        
    }
    
    request_size = request_size + 8;
    int alloc_size = MINIMUM_ALLOC;

    while(alloc_size < request_size)
        alloc_size *= 2;    
    alloc_ptr = gronk(free_list, alloc_size);
	alloc_ptr = (void *)alloc_ptr;    
	return alloc_ptr;    
}

void free(void *memory_block)
{
    int *header_ptr = memory_block;
    header_ptr -= 2;

    //find the last free block
    int *last_free = free_list;
    while(last_free[1] != 0)
    {
        last_free += last_free[1]/4;
    }
    //insert freed block into the free list, i.e. correct offsets

    if(last_free < header_ptr) //header_ptr needs to be the new last free block
    {
        int offset = last_free[0];
        int *temp = last_free;
        while((temp + (temp[0]/4) + 1) == 0 && temp + temp[0]/4 != header_ptr) 
        //while the next block is allocated and is not the newly freed block
        {  
            temp += temp[0]/4; //move temp the size of the allocated block
            offset += temp[0]; //add the size of the next block to offset
        }
        last_free[1] = offset; 
    }
    else //find what the offset needs to be for the freed block
    {
        int offset = header_ptr[0];
        int *temp = header_ptr;
        while((temp + (temp[0]/4) + 1) == 0 && (temp + temp[0]/4) != last_free)
        //while the next block is allocated and is not the last free block
        {
            temp += temp[0]/4; //move temp the size of the allocated block
            offset += temp[0]; //add the size of the next block to offset
        }
        header_ptr[1] = offset;
        if(header_ptr < free_list)//check if the freed block should be the new freelist head
        {
            free_list = header_ptr;
        }
        else // update the offset of the free block above the newly freed block
        {
            free_offset_updater(header_ptr);
        }
    }
    tom_brady(header_ptr);
}
/*
The tom_brady function is the function responsible for methodically scanning the heap to find the 
correct buddy of the memory block. If the buddy is free the two blocks are coalesced and tom_brady 
is recursively called again until the buddy cannot be coalesced. the tom_brady function manages the 
heap in the same way that Tom Brady (Quarterback of the New England Patriots, if you didn't know) 
methodically manages his offense. 
*/
int *tom_brady(int *mem_block)
{
	int *heap_ptr = heap_begin;
	int count = 1;			//starts at 1 to count the block itself
	int cumulative = 0;
	int last_size = 0;
	while (heap_ptr != mem_block)  //passes through the heap until the passed in memory block is met
	{
		if (heap_ptr[0] < mem_block[0])	
		{
			cumulative += heap_ptr[0];
			if (cumulative < mem_block[0])
			{
				heap_ptr += heap_ptr[0]/4;
				last_size = heap_ptr[0];
				continue;		//count is not incremented because cumulative is not yet of the same size
			}					//as the passed in memory block
		}
		if (heap_ptr[0] > mem_block[0])
		{
			heap_ptr += heap_ptr[0]/4; 	//count is not incremented because the block is too big 
			last_size = heap_ptr[0];			
			continue;
		}
		last_size = heap_ptr[0];
		cumulative = 0;				//count increments either when an accumulation of small memory blocks
		count++; 					//reach the size of the passed in memory block or when the heap_ptr
		heap_ptr += heap_ptr[0]/4;	//points to a memory block of equal size
	}
	int *before = heap_ptr - (last_size / 4);
	int *next = heap_ptr + (heap_ptr[0] / 4);
	if (count % 2)		//if the count is odd we look at the next pointer 
	{					//because it is the first buddy (when sequentially looking through the heap)
		if (next[0] == mem_block[0] && next[1] >= mem_block[0])
		{
			mem_block[0] *= 2;
			mem_block[1] += next[1];
			next[0] = 0;
			next[1] = 0;
			return tom_brady(mem_block);	//open buddy is found and tom_brady is called again
		}
		else
			return mem_block;			//no open buddy, nothing is coalesced
	}
	else				//the count is even so we look at the before pointer 
	{					//because it is the second of the two buddies (sequentially)
		if (before[0] == mem_block[0] && before[1] > 0) 
		{
			before[0] *= 2;
			mem_block[0] = 0;
			mem_block[1] = 0;
			return tom_brady(before);	//open buddy at the before pointer, tom_brady is called again
		}
		else
			return mem_block;	//no open buddy, nothing is coalesced
	}
}
		

/*void dump_memory_map(void) {
    int *heap_ptr = heap_begin;
    int *free_ptr = free_list;
    int offset = 0;
    printf("~~~~~~~~~~~~~~~~~~~~Memory Dump~~~~~~~~~~~~~~~~~~~~\n");
    if (heap_ptr != free_ptr)		//checks for allocated memory before the freelist pointer
    {
	    int size = 0;
	    while (heap_ptr != free_ptr)
	    {
	        size += heap_ptr[0];
	        heap_ptr += (heap_ptr[0]/4);
	    }
	    printf("Block size: %d, offset %d, allocated\n", size, offset);
	    offset = size;
    }
    while (free_ptr[1] != 0) 		//traverses through the free memory list
    {
	    int alloc_size = free_ptr[1] - free_ptr[0];
	    if (alloc_size != 0)		//takes into account allocated memory that is bypassed in the offset
	    {
	        printf("Block size: %d, offset %d, free\n", free_ptr[0], offset);
	        offset += free_ptr[0];
	        printf("Block size: %d, offset %d, allocated\n", alloc_size, offset);
	        offset += alloc_size;
	    }
	    else				//next block is free memory
	    {
	        printf("Block size: %d, offset %d, free\n", free_ptr[0], offset);
	        offset += free_ptr[0];
	    }
	    free_ptr += (free_ptr[1]/4);
    }
    printf("Block size: %d, offset %d, free\n", free_ptr[0], offset);
    offset += free_ptr[0];
    if (HEAPSIZE > offset)		//checks for allocated memory at the end of the heap,
    {					//after the last free memory space
	    int last_size = HEAPSIZE - offset;
	    printf("Block size: %d, offset %d, free\n", last_size, offset);
	    offset += last_size;
    }
    printf("~~~~~~~~~~~~~~~~~~End Memory Dump~~~~~~~~~~~~~~~~~~\n");
    return;
}*/


void offset_updater(int *heap_ptr, int old_offset) 
{
    int *temp_ptr = free_list;
    while ((temp_ptr + temp_ptr[1]/4) != heap_ptr || temp_ptr[1] == 0)
    {
        if(temp_ptr[1] == 0){
            return;}
        temp_ptr += temp_ptr[1]/4;
    }
    if(old_offset == 0){
        temp_ptr[1] = 0;}
    else{
        temp_ptr[1] += old_offset;}
    return;
}

void free_offset_updater(int *header_ptr)
{
    int *temp = free_list;
    while(temp + temp[1]/4 < header_ptr)//traverse the list until the free block immediately above the newly freed block
    {
        temp += temp[1]/4;
    }
    int offset = header_ptr - temp;
    //printf("offset = %d\n", offset);
    temp[1] = offset;
}