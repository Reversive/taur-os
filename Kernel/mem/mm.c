// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/* Based on FreeRTOS Kernel V10.4.3
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS */

#include "include/mm.h"

// ------------------------------DECLARACION DE FUNCIONES----------------------------------//

typedef struct Header {
    struct Header * next;
    size_t size;
} header;

/* Inserts a block of memory to the list of free mem blocks.
 * Merges adjacent free zones into one. */
static void addBlockToFreeList(header * blockToInsert);

/* Sets up the required heap on the first call to malloc */
static void initHeap();

/* The size of the structure placed at the beginning of each
 * allocated memory block must be correctly byte aligned. */
static const size_t heapConstructSize = (sizeof(header) + ((size_t) (BYTE_ALIGNMENT - 1))) & ~((size_t) BYTE_ALIGNMENT_MASK);

#define HEAP_MINIMUM_BLOCK_SIZE ((size_t) (heapConstructSize << 1 ))

/* Links to the free list*/
static header start, * pEnd = NULL;

static size_t freeBytesRemaining = 0;

void * totalMemory;

/* Gets set to the top bit of a size_t type. If this bit in the
 * size member of a header structure is set, then the block belongs
 * to the application. When the bit is free, the block is still part
 * of the free heap space. */
static size_t xBlockAllocatedBit = 0;


//-----------------------------------------------------------------------------------------//

int info[2] = {0};

int * mem_info()
{
    info[0] = TOTAL_HEAP_SIZE;
    info[1] = freeBytesRemaining;
    return info;
}

void * malloc(size_t requestedSize)
{
    header * currp, * prevp, *insertp;
    void * returnp = NULL;

    if(pEnd == NULL)
    {
        initHeap();
    }

    if((requestedSize & xBlockAllocatedBit) == 0)      // Checks that the requested block doesn't set the top bit
    {
        if((requestedSize > 0) && ((requestedSize + heapConstructSize) >  requestedSize))       // The wanted size is smaller than the block size
        {                                                                                       // so we are going to make it larger
            requestedSize += heapConstructSize;
            
            if((requestedSize & BYTE_ALIGNMENT_MASK) != 0x00)    // Align blocks if needed
            {
                // Check for overflow.
                if( (requestedSize + (BYTE_ALIGNMENT - (requestedSize & BYTE_ALIGNMENT_MASK)))  > requestedSize)
                {
                    requestedSize += (BYTE_ALIGNMENT - (requestedSize & BYTE_ALIGNMENT_MASK));
                } else
                {
                    requestedSize = 0;
                }  
            }
        }

        if((requestedSize > 0) && ( requestedSize <= freeBytesRemaining))       // We have free space for the requested size
        {                                                                       // Traverse the list from the start	block (lowest address) to find an adequate sized block
            prevp = &start;
            currp = start.next;

            while((currp->size < requestedSize) && (currp->next != NULL))
            {
                prevp = currp;
                currp = currp->next;
            }

            if(currp != pEnd)       // If this happens, then the adequate block wasn't found
            {
                returnp = (void *) (((uint8_t *) prevp->next) + heapConstructSize);     // Return the memory space, jumping over the header structure at its start
                prevp->next = currp->next;      // Take out the block from the free list

                if((currp->size - requestedSize) > HEAP_MINIMUM_BLOCK_SIZE)         // If the block is bigger than the required size, split it into two
                {
                    insertp = (void *) (((uint8_t *) currp) + requestedSize);       // Create a new block following the number of bytes requested. The (void *) cast is used to prevent byte alignment warnings
                    insertp->size = currp->size - requestedSize;        // Calculate the sizes of the new two blocks
                    currp->size = requestedSize;
                    addBlockToFreeList(insertp);        // Insert the new block into the list of free blocks
                }

                freeBytesRemaining -= currp->size;
                currp->size |= xBlockAllocatedBit;      // The block is marked as allocated and owned by the app
                currp->next = NULL;
            }
        }
    }
    return returnp;
}



static void initHeap()
{
    
    header * pFirstFreeBlock;
    uint8_t * pAlignedHeap;
    size_t totalMemPointer;
    size_t totalHeapSize = TOTAL_HEAP_SIZE;

    sbrkHandler(TOTAL_HEAP_SIZE, &totalMemory);
    totalMemPointer = (size_t) totalMemory;         // Ensure the heap starts on a correctly aligned boundary
    
    if( ( totalMemPointer & BYTE_ALIGNMENT_MASK ) != 0 )        // Checks the last bits and if they are not aligned then we align them
    {
        totalMemPointer += ( BYTE_ALIGNMENT - 1 );
        totalMemPointer &= ~((size_t) BYTE_ALIGNMENT_MASK);
        totalHeapSize -= totalMemPointer - (size_t) totalMemory;
    }

    pAlignedHeap = (uint8_t *) totalMemPointer;
    start.next = (void *) pAlignedHeap;             // Pointer to the first item in the list of free blocks
    start.size = (size_t) 0;
    totalMemPointer = ((size_t) pAlignedHeap) + totalHeapSize;
    totalMemPointer -= heapConstructSize;
    totalMemPointer &= ~((size_t) BYTE_ALIGNMENT_MASK);
    pEnd = (void *) totalMemPointer;                // Pointer to the end of the list of free blocks, inserted at the end of the heap space
    pEnd->size = 0;
    pEnd->next = NULL;
    pFirstFreeBlock = (void *) pAlignedHeap;        // Single free block that is sized to take up the entire heap space, minus the pEnd space
    pFirstFreeBlock->size = totalMemPointer - (size_t) pFirstFreeBlock;
    pFirstFreeBlock->next = pEnd;
    freeBytesRemaining = pFirstFreeBlock->size;     // Only one block exists, covering the entire usable heap space
    xBlockAllocatedBit = ((size_t) 1) << ((sizeof(size_t) * heapBITS_PER_BYTE) - 1);    // Work out the position of the top bit in a size_t variable
}


void free(void *ptr)
{

    uint8_t * currp = (uint8_t *) ptr;
    header * insertp;

    if(ptr != NULL)     // The memory being freed will have a header structure immediately before it
    {
        currp -= heapConstructSize;
        insertp = (void *) currp;   // Cast avoiding compiler warnings

        if((insertp->size & xBlockAllocatedBit) != 0)
        {
            if(insertp->next == NULL)
            {
                insertp->size &= ~xBlockAllocatedBit;   // The block is no longer allocated
                freeBytesRemaining += insertp->size;    // Add this block to the list of free blocks
                addBlockToFreeList(((header *) insertp));
            }
        }
    }
}


static void addBlockToFreeList(header * blockToInsert)
{
    
    header * iteratorp;
    uint8_t * currp;

    iteratorp = &start;
    while(iteratorp->next < blockToInsert)      // Iterate through the list until a block is found that has
    {                                           // a higher address than the block being inserted
        iteratorp = iteratorp->next;
    }

    currp = (uint8_t *) iteratorp;
    if((currp + iteratorp->size) == (uint8_t *) blockToInsert)  // The block being inserted makes a contiguous
    {                                                           // block of memory with the one on its left
        iteratorp->size += blockToInsert->size;                 // So we merge
        blockToInsert = iteratorp;
    }

    currp = (uint8_t *) blockToInsert;
    if((currp + blockToInsert->size) == (uint8_t *) iteratorp->next)    // The block being inserted makes a contiguous
    {                                                                   // block of memory with the one on its right
        if(iteratorp->next != pEnd)                                     // So we merge (if it's not the end)
        {
            blockToInsert->size += iteratorp->next->size;
            blockToInsert->next = iteratorp->next->next;
        } else
        {
            blockToInsert->next = pEnd;
        }
    } else
    {
        blockToInsert->next = iteratorp->next;
    }

    if(iteratorp != blockToInsert)          // If the block was merged with the block before and after him,
    {                                       // then the ptr has been set already and shouldn't change here
        iteratorp->next = blockToInsert;    // (or it would point to itself)
    }
}