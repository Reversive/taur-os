#ifndef SEM_H
#define SEM_H

#include "../../include/lib.h"
#include "../../task/include/process.h"
#include "../../dispatcher/include/scheduler.h"
#include <stdint.h>

#define MAX_PROC 50
#define MAX_SEMS 256
#define NAME_CHAR_LIMIT 1024
#define OUT_OF_BOUNDS -1
#define ERROR -1

typedef struct semInfo {
    int semId;
    char name[NAME_CHAR_LIMIT];
    uint64_t lock;   // lock
    uint64_t value;
    uint64_t openCount;    // Counter of pending 'close' signals
    uint64_t blockedProcesses[MAX_PROC];
    uint64_t blockedFirst;
    uint64_t blockedLast;
} semInfo_t;

int semOpen(char *semName, int initValue);
int	semWait(char *semName);
int semPost(char *semName);
int semClose(char *semName);
int getSemsCount();
int getSemInfo(int idx, semInfo_t *buffer);

#endif