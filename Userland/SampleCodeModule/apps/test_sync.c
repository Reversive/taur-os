#include "include/test_sync.h"
#include "../include/console.h"

#define TOTAL_PAIR_PROCESSES 3
#define SEM_ID "sem"
#define N "20"

int64_t global;  //shared memory

void slowInc(int64_t *p, int64_t inc){
  int64_t aux = *p;
  aux += inc;
  sys_yield();
  *p = aux;
}

void inc(uint64_t sem, int64_t value, uint64_t n){
  uint64_t i;

  if (sem && sys_sem_open(SEM_ID, 1) < 0){
    printf("ERROR OPENING SEM\n");
    return;
  }
  
  for (i = 0; i < n; i++){
    if (sem) sys_sem_wait(SEM_ID);
    slowInc(&global, value);
    if (sem) sys_sem_post(SEM_ID);
  }

  if (sem) sys_sem_close(SEM_ID);
  
  printf("Final value: %d\n", global);
}

int inc_main(int argc, char **argv){
  inc(atoi(argv[0]), atoi(argv[1]), atoi(argv[2]));
  return 0;
}

parameters arg1 = {"1", "1", N, NULL};
parameters arg2 = {"1", "-1", N, NULL};
int test_sync(int argc, char **argv){
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...(WITH SEM)\n");

  for(i = 0; i < TOTAL_PAIR_PROCESSES; i++){
    execv("inc", inc_main, arg1);
    execv("inc", inc_main, arg2);
  }
  return 0;
}


parameters arg1_no = {"0", "1", N, NULL};
parameters arg2_no = {"0", "-1", N, NULL};
int test_no_sync(int argc, char **argv){
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...(WITHOUT SEM)\n");

  for(i = 0; i < TOTAL_PAIR_PROCESSES; i++){
    execv("inc", inc_main, arg1_no);
    execv("inc", inc_main, arg2_no);
  }
  return 0;
}