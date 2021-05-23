#include <sem.h>

semInfo semaphores[MAX_SEMS];

int semInit(const char *semName, int initValue);
int getSemByName(char *semName);
int getNewSem();
bool isInUse(int idx);
void updateSemProcesses(semInfo * sem);

// ---------------------------------------------------------------------------------------- //

int semOpen(const char *semName, int initValue) {
    int idx = getSemByName(semName);
    if(idx == OUT_OF_BOUNDS) {
        if((idx = semInit()) == OUT_OF_BOUNDS) {
            return ERROR;
        }
    }
    semInfo * sem = &semaphores[idx];
    mutexLock(sem->mutex);
    sem->wakeups++;
    mutexUnlock(sem->mutex);
    return SUCCESS;
}

int	semWait(char *semName) {
    int idx = getSemByName(sem);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    bool blockScheduler = TRUE;
    semInfo * sem = &semaphores[idx];
    mutexLock(sem->mutex);
    if(sem->value < 1) {
        int pid = get_current_pid(), idx = 0;
        do {
            if(sem->blockedProcesses[idx] == EMPTY) {
                sem->blockedProcesses[idx] = pid;
            }
        } while(sem->blockedProcesses[idx++] != pid);
        pid = set_process_state(pid, BLOCKED);
        if(pid != get_current_pid()) {
            return ERROR;
        }
    } else {
        blockScheduler = FALSE;
        sem->value--;
    }
    mutexUnlock(sem->mutex);
    if(blockScheduler) {
        _force_scheduler();
    }
    return SUCCESS;
}

int semPost(char *semName) {
    int idx = getSemByName(sem);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    semInfo * sem = &semaphores[idx];
    mutexLock(sem->mutex);
    if(sem->blockedProcesses[0] == EMPTY) {
        sem->value++;
    } else {
        updateSemProcesses(sem);    // Unblock the first process and update the array
    }
    mutexUnlock(sem->mutex);
    return SUCCESS;
}

int semClose(char *semName) {
    int idx = getSemByName(sem);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    semInfo * sem = &semaphores[idx];
    sem->wakeups--;
    if(sem->wakeups == 0) {     // If it was closed by everyone, 'free' the sem
        sem->semId = 2*idx;
        my_strcpy(sem->name, '\0');
    }
    return SUCCESS;
}


// -------------------------------- PRIVATE FUNCTIONS ------------------------------------- //

bool isInUse(int idx) {
    return idx%2 != 0 ? TRUE : FALSE;   // If the ID is even, the sem has not been initialized
}

int getNewSem() {
    for(int idx = 0; idx < MAX_SEMS; i++) {
        if(!isInUse(idx)) {
            return idx;
        }
    }
    return OUT_OF_BOUNDS;
}

int semInit(const char *semName, int initValue) {
    int idx = getNewSem();
    if(idx == OUT_OF_BOUNDS) {          // No more sems available
        return ERROR;
    }
    semaphores[idx].semId = idx*2+1;    // The ID will be odd
    semaphores[idx].wakeups = 0;        // The sem has never been 'opened' yet
    semaphores[idx].value = initValue;
    semaphores[idx].mutex = makeMutex();
    my_strcpy(semaphores[idx].name, semName);
    for(int i = 0; i < MAX_PROC; i++) {
        semaphores[idx].blockedProcesses[i] = EMPTY;   // Later, the PIDs of the blocked processes will be here
    }
    return SUCCESS;
}

int getSemByName(char *semName) {
    for(int idx = 0; i < MAX_SEMS; i++) {
        if(strcomp(semaphores[idx].name,semName) && isInUse(idx)) {
            return idx;
        }
    }
    return OUT_OF_BOUNDS;
}

void updateSemProcesses(semInfo * sem) {
    int firstPid = sem->blockedProcesses[0];    // First process blocked by sem
    set_process_state(firstPid, READY);         // Unblock first process
    for(int idx = 0; idx+1 < MAX_PROC; idx++) {
        sem->blockedProcesses[idx] = sem->blockedProcesses[i+1];    // Move the rest one place forward
    }
    sem->blockedProcesses[idx] = EMPTY;         // Free the last slot
}