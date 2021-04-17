#include <unistd.h>  // sbrk
#include "memManager.h"

#define NALLOC 1024  // Number of block sizes to allocate on call to sbrk
#ifdef NULL
#undef NULL
#endif
#define NULL 0
#define TOTAL_MEM 1024

// long is chosen as an instance of the most restrictive alignment type


struct Header {
  struct Header *next;
  unsigned size;
} header;

char totalMem[TOTAL_MEM];
char* memptr = totalMem; 

struct Header base;           // Used to get an initial member for free list
struct Header *freep = NULL;  // Free list starting point


struct Header *morecore(unsigned nblocks);
void kandr_free(void *ptr);




void *kandr_malloc(unsigned nbytes) {

  struct Header *currp;
  struct Header *prevp;
  unsigned nunits;
  nunits = ((nbytes + sizeof(struct Header) - 1) / sizeof(struct Header)) + 1;

  if (freep == NULL) {

    // Create degenerate free list; base points to itself and has size 0
    base.next = &base;
    base.size = 0;

    // Set free list starting point to base address
    freep = &base;
  }

  prevp = freep;
  currp = prevp->next;

  for (; ; prevp = currp, currp = currp->next) {

    if (currp->size >= nunits) {
      if (currp->size == nunits) {
        prevp->next = currp->next;
      }
      
      else {
        // Changes the memory stored at currp to reflect the reduced block size
        currp->size -= nunits;
        // Find location at which to create the block header for the new block
        currp += currp->size;
        // Store the block size in the new header
        currp->size = nunits;
      }
      freep = prevp;

      return (void *) (currp );

    } 
    if (currp == freep) {
      if ((currp = morecore(nunits)) == NULL) {
        return NULL;
      }
    } // end wrapped around free list case
  } // end step through free list looking for memory loop
}




struct Header *morecore(unsigned nunits) {

  void *freemem;    // The address of the newly created memory
  struct Header *insertp;  // Header ptr for integer arithmatic and constructing header
  // if (nunits < NALLOC) {
  //   nunits = NALLOC;
  // }
  // freemem = sbrk(nunits * sizeof(struct Header));
  if(memptr + nunits > totalMem + TOTAL_MEM){
    return NULL;
  }
  freemem = memptr;
  memptr +=nunits;
  // if (freemem == (void *) -1) {
  //   return NULL;
  // }

  // Construct new block
  insertp = (struct Header *) freemem;
  insertp->size = nunits;

  kandr_free((void *) insertp );

  return freep;
}




void kandr_free(void *ptr) {

  struct Header *insertp, *currp;

  // Find address of block header for the data to be inserted
  insertp = (struct Header *) ptr;

  
  for (currp = freep; !((currp < insertp) && (insertp < currp->next)); currp = currp->next) {

    if ((currp >= currp->next) && ((currp < insertp) || (insertp < currp->next))) {
      break;
    }
  }
  if ((insertp + insertp->size) == currp->next) {
    insertp->size += currp->next->size;
    insertp->next = currp->next->next;
  }
  else {
    insertp->next = currp->next;
  }
  if ((currp + currp->size) == insertp) {
    currp->size += insertp->size;
    currp->next = insertp->next;
  }
  else {
    currp->next = insertp;
  }

  freep = currp;
}