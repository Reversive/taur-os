#include "include/sem.h"
#include <stdbool.h>
#include "../asm/include/libasm.h"
#include "../dispatcher/include/scheduler.h"

#define NO_PID -1
#define SUCCESS 1

semInfo_t semaphores[MAX_SEMS];

int semInit(char *semName, int initValue);
int getSemByName(char *semName);
int getNewSem();
bool isInUse(int idx);
void updateSemProcesses(semInfo_t * sem);

// ---------------------------------------------------------------------------------------- //

int semOpen(char *semName, int initValue) {
    int idx = getSemByName(semName);
    if(idx == OUT_OF_BOUNDS) {
        if((idx = semInit(semName, initValue)) == OUT_OF_BOUNDS) {
            return ERROR;
        }
    }
    semInfo_t * sem = &semaphores[idx];
    int count;
    do count = sem->openCount; 
    while(_cmpxchg(&sem->openCount, count+1, count) != count);  // Atomic add
    return SUCCESS;
}

int	semWait(char *semName) {

    // This macro guarantees that only one semaphore satifies it,
    // because only one sem has the lock and a value greater than zero.
    // The last part (by lazy OR) frees the lock if the value is less than zero.
    #define cond (!_xchg(&sem->lock, 1) && (sem->value > 0 || (sem->lock = 0)))

    int idx = getSemByName(semName);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    semInfo_t * sem = &semaphores[idx];
    while(!cond) {                          // Sleeping loop
        int pid = get_current_pid();
        scheduler_disable();                // From here it can't change the process => No race conditions
        // set_process_state(pid, BLOCKED); // DISABLED. It used to block the current process
        uint64_t last;
        do {                                // Searchs for a place in the list of blocked processes, and adds itself
            last = sem->blockedLast;
            sem->blockedProcesses[last % MAX_PROC] = pid;
        }
        while(_cmpxchg(&sem->blockedLast, last+1, last) != last);   // Atomic add
        if(cond) {                          // Checks changes (they could be made by interrupts)
            while((last = sem->blockedLast) - sem->blockedFirst > 0 && _cmpxchg(&sem->blockedLast, last-1, last) != last);  // The difference between the counters is the quantity of blocked processes. Atomic decrement of last
            set_process_state(pid, READY);  // Unlocks the process
            scheduler_enable();             // Unlocks the scheduler
            break;
        }
        scheduler_enable();
        _force_scheduler();
    }
    sem->value--;   // Only one process gets here
    sem->lock = 0;

    return SUCCESS;
    #undef cond
}

int semPost(char *semName) {
    int idx = getSemByName(semName);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    semInfo_t * sem = &semaphores[idx];
    scheduler_disable();
    uint64_t value;
    do value = sem->value;
    while(_cmpxchg(&sem->value, value+1, value) != value);
    updateSemProcesses(sem);    // Unblock the first process and update the array
    scheduler_enable();
    return SUCCESS;
}

int semClose(char *semName) {
    int idx = getSemByName(semName);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    semInfo_t * sem = &semaphores[idx];
    sem->openCount--;
    if(sem->openCount == 0) {     // If it was closed by everyone, 'free' the sem
        sem->semId = 2*idx;
        my_strcpy(sem->name, "");
    }
    return SUCCESS;
}

int getSemInfo(int idx, semInfo_t *buffer) {
    if (idx < 0 || idx >= MAX_SEMS) {
        return ERROR;
    }
    buffer->semId = semaphores[idx].semId;
	my_strcpy(buffer->name, semaphores[idx].name);
	buffer->value = semaphores[idx].value;
	for (int j = 0; j < semaphores[idx].openCount; j++)	{
		buffer->blockedProcesses[j] = semaphores[idx].blockedProcesses[j];
		buffer->openCount++;
	}
    return SUCCESS;
}

int getSemsCount() {
    int counter = 0;
    for(int idx = 0; idx < MAX_SEMS; idx++) {
        if(isInUse(semaphores[idx].semId)) {
            counter++;
        }
    }
    return counter;
}

// -------------------------------- PRIVATE FUNCTIONS ------------------------------------- //

bool isInUse(int idx) {
    return idx%2 != 0 ? true : false;   // If the ID is even, the sem has not been initialized
}

int getNewSem() {
    for(int idx = 0; idx < MAX_SEMS; idx++) {
        if(!isInUse(idx)) {
            return idx;
        }
    }
    return OUT_OF_BOUNDS;
}

int semInit(char *semName, int initValue) {
    int idx = getNewSem();
    if(idx == OUT_OF_BOUNDS) {          // No more sems available
        return ERROR;
    }
    semaphores[idx].semId = idx*2+1;    // The ID will be odd
    semaphores[idx].openCount = 0;      // The sem has never been 'opened' yet
    semaphores[idx].value = initValue;
    semaphores[idx].blockedFirst = 0;
    semaphores[idx].blockedLast = 0;
    semaphores[idx].lock = 0;

    my_strcpy(semaphores[idx].name, semName);
    for(int i = 0; i < MAX_PROC; i++) {
        semaphores[idx].blockedProcesses[i] = NO_PID;   // Later, the PIDs of the blocked processes will be here
    }
    return SUCCESS;
}

int getSemByName(char *semName) {
    for(int idx = 0; idx < MAX_SEMS; idx++) {
        if(strcomp(semaphores[idx].name,semName) == 0 && isInUse(semaphores[idx].semId)) {
            return idx;
        }
    }
    return OUT_OF_BOUNDS;
}

void updateSemProcesses(semInfo_t * sem) {
    uint64_t idx;
    bool awake = true;
    while(sem->blockedLast - (idx = sem->blockedFirst) > 0 || (awake = false)) {
        if(_cmpxchg(&sem->blockedFirst, idx + 1, idx) == idx)
            break;
    }
    if(awake) {
        int pid = sem->blockedProcesses[idx % MAX_PROC];  // First process blocked by sem
        set_process_state(pid, READY);                    // Unblock first process
    }
}