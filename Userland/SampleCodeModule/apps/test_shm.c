#include "include/test_shm.h"

char * mutex;
int key = 0;

int read(int argc, char **argv) {
    sys_sem_wait(mutex);
    void * shm = sys_shm_open(key);
    printf("%s\n",(char*)shm);
    sys_sem_post(mutex);
    return 0;
}

int write(int argc, char **argv) {
    sys_sem_wait(mutex);
    void * shm = sys_shm_open(key);
    strcpy(shm, "SHM TEST\n");
    sys_sem_post(mutex);
    return 0;
}

int shm_test(int argc, char **argv) {
    strcpy(mutex, "mutex");
    sys_sem_open("mutex", 1);
    execv("write", write,(char*[]){NULL}, 0);
    execv("read", read,(char*[]){NULL}, 0);
    return 0;    
}