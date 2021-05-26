// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/test_mm.h"

#define MAX_BLOCKS 128
#define MAX_MEMORY 1024 //Should be around 80% of memory managed by the MM

typedef struct MM_rq{
  void *address;
  uint32_t size;
}mm_rq;

void test_mm(){
  mm_rq mm_rqs[MAX_BLOCKS];
  while (1){
    uint8_t rq = 0;
    int32_t total = 0;

    // Request as many blocks as we can
    while(rq < MAX_BLOCKS && total < MAX_MEMORY){
      mm_rqs[rq].size = GetUniform(MAX_MEMORY - total - 1) + 1;
      mm_rqs[rq].address = sys_malloc(mm_rqs[rq].size); // TODO: Port this call as required
      if(mm_rqs[rq].address == 0) {
        printfd("malloc: NULL pointer returned\n");
        // exit(-1);
        break;
      }
      total += mm_rqs[rq].size;
      rq++;
    }

    // Set
    uint32_t i;
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address != 0)
        memset(mm_rqs[i].address, i, mm_rqs[i].size); // TODO: Port this call as required

    // Check
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address != 0)
        if(!memcheck(mm_rqs[i].address, i, mm_rqs[i].size))
          printfd("memcheck: ERROR!\n"); // TODO: Port this call as required

    // Free
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address != 0)
        sys_free(mm_rqs[i].address);  // TODO: Port this call as required
  } 
}

int main_test_mm(int argc, char **argv) {
    test_mm();
    sys_sem_post("pipe");
    return 0;
}