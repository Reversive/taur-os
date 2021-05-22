// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/test_processes.h"
int endless_loop(int argc, char **argv){
  while(1);
}

#define MAX_PROCESSES 5

typedef struct P_rq{
  uint32_t pid;
  process_status_et state;
}p_rq;

void test_processes(){
  p_rq p_rqs[MAX_PROCESSES];
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;

  while (1) { 

    for(rq = 0; rq < MAX_PROCESSES; rq++){
      p_rqs[rq].pid = execv("endless_loop", endless_loop, (char*[]){NULL});
      printf("created %d\n", p_rqs[rq].pid);
      if (p_rqs[rq].pid == -1){                          
        printf("Error creating process\n");              
        return;
      }else{
        p_rqs[rq].state = READY;
        alive++;
      }
    }

   
    while (alive > 0) {
      for(rq = 0; rq < MAX_PROCESSES; rq++){
        action = GetUniform(2) % 2; 

        switch(action){
          case 0:
            if (p_rqs[rq].state == READY || p_rqs[rq].state == BLOCKED) {
              if (kill(p_rqs[rq].pid) == -1) {          
                printf("Error killing process\n");        
                return;
              }
              p_rqs[rq].state = KILLED; 
              alive--;
            }
            break;

          case 1:
            if (p_rqs[rq].state == READY){
              if(block(p_rqs[rq].pid) == -1){          
                printf("Error blocking process\n");       
                return;
              }
              p_rqs[rq].state = BLOCKED; 
            }
            break;
        }
      }

      for(rq = 0; rq < MAX_PROCESSES; rq++)
        if (p_rqs[rq].state == BLOCKED && GetUniform(2) % 2){
          if(block(p_rqs[rq].pid) == -1){            
            printf("Error unblocking process\n");         
            return;
          }
          p_rqs[rq].state = READY; 
        }
    } 
  }
}

int test_processes_main(int argc, char **argv){
  test_processes();
  return 0;
}
