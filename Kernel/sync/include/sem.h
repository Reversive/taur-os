#ifndef SEM_H
#define SEM_H

    #include "mutex.h"
    #include "../../include/lib.h"
    #include "../../task/include/process.h"
    #include "../../dispatcher/include/scheduler.h"
    #include "../../asm/include/libasm.h"

    #define MAX_PROC 32
    #define MAX_SEMS 256
    #define NAME_CHAR_LIMIT 1024
    #define OUT_OF_BOUNDS -1
    #define EMPTY -1
    #define ERROR -1
    #define SUCCESS 0

    typedef enum { FALSE, TRUE } bool;
    
    typedef struct semInfo {
        int semId;
        char name[NAME_CHAR_LIMIT];
        Mutex *mutex;   // Mutex as lock
        int value;
        int wakeups;    // Counter of pending 'close' signals
        int blockedProcesses[MAX_PROC];
    } semInfo_t;

    int semOpen(const char *semName, int initValue);
    int	semWait(char *semName);
    int semPost(char *semName);
    int semClose(char *semName);
    // getSemsInfo();

#endif