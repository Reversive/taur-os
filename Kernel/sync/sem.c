// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/sem.h"
#include <stdbool.h>
#include <stdint.h>
#include "../asm/include/libasm.h"
#include "../dispatcher/include/scheduler.h"

#define NO_PID -1
#define SUCCESS_SIGNAL 0

sem_ts semaphores[MAX_SEMS];

int sem_init(char *name, int value);
int get_sem_by_name(char *name);
int get_new_sem();
bool is_in_use(int idx);
void update_sem_processes(p_sem sem);

int sem_open(char *name, int value) {
    int idx = get_sem_by_name(name);
    if(idx == OUT_OF_BOUNDS) {
        if((idx = sem_init(name, value)) == OUT_OF_BOUNDS) {
            return ERROR;
        }
    }
    p_sem sem = &semaphores[idx];
    int count;
    do count = sem->open_count; 
    while(_cmpxchg(&sem->open_count, count+1, count) != count);  // Atomic add
    return SUCCESS_SIGNAL;
}

int	sem_wait(char *name) {

    // This macro guarantees that only one semaphore satisfies it,
    // because only one sem has the lock and a value greater than zero.
    // The last part (by lazy OR) frees the lock if the value is less than zero.
    #define cond (!_xchg(&sem->lock, 1) && (sem->value > 0 || (sem->lock = 0)))

    int idx = get_sem_by_name(name);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    p_sem sem = &semaphores[idx];
    while(!cond) {                          // Sleeping loop
        int pid = get_current_pid();
        scheduler_disable();                // From here it can't change the process => No race conditions
        // set_process_state(pid, BLOCKED); // DISABLED. It used to block the current process
        uint64_t last;
        do {                                // Searchs for a place in the list of blocked processes, and adds itself
            last = sem->blocked_last;
            sem->blocked_processes[last % MAX_PROC] = pid;
        }
        while(_cmpxchg(&sem->blocked_last, last+1, last) != last);   // Atomic add
        if(cond) {                          // Checks changes (they could be made by interrupts)
            while((last = sem->blocked_last) - sem->blocked_first > 0 && _cmpxchg(&sem->blocked_last, last-1, last) != last);  // The difference between the counters is the quantity of blocked processes. Atomic decrement of last
            set_process_state(pid, READY);  // Unlocks the process
            scheduler_enable();             // Unlocks the scheduler
            break;
        }
        scheduler_enable();
        _force_scheduler();
    }
    sem->value--;   // Only one process gets here
    sem->lock = 0;

    return SUCCESS_SIGNAL;
    #undef cond
}

int sem_post(char *name) {
    int idx = get_sem_by_name(name);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    p_sem sem = &semaphores[idx];
    scheduler_disable();
    uint64_t value;
    do value = sem->value;
    while(_cmpxchg(&sem->value, value+1, value) != value);
    update_sem_processes(sem);    // Unblock the first process and update the array
    scheduler_enable();
    return SUCCESS_SIGNAL;
}

int sem_close(char *name) {
    int idx = get_sem_by_name(name);
    if(idx == OUT_OF_BOUNDS) {
        return ERROR;
    }
    p_sem sem = &semaphores[idx];
    uint64_t c = --(sem->open_count);
    if((int)c < 1) {     // If it was closed by everyone, 'free' the sem
        sem->sem_id = 2*idx;
        my_strcpy(sem->name, "");
    }
    return SUCCESS_SIGNAL;
}

int get_sem_info(int idx, p_sem buffer) {
    if (idx < 0 || idx >= MAX_SEMS) {
        return ERROR;
    }
    buffer->sem_id = semaphores[idx].sem_id;
	my_strcpy(buffer->name, semaphores[idx].name);
	buffer->value = semaphores[idx].value;
	for (int j = 0; j < semaphores[idx].open_count; j++)	{
		buffer->blocked_processes[j] = semaphores[idx].blocked_processes[j];
		buffer->open_count++;
	}
    return SUCCESS_SIGNAL;
}

int get_sem_count() {
    int counter = 0;
    for(int idx = 0; idx < MAX_SEMS; idx++) {
        if(is_in_use(semaphores[idx].sem_id)) {
            counter++;
        }
    }
    return counter;
}

// -------------------------------- PRIVATE FUNCTIONS ------------------------------------- //

bool is_in_use(int idx) {
    return idx%2 != 0 ? true : false;   // If the ID is even, the sem has not been initialized
}

int get_new_sem() {
    for(int idx = 0; idx < MAX_SEMS; idx++) {
        if(!is_in_use(semaphores[idx].sem_id)) {
            return idx;
        }
    }
    return OUT_OF_BOUNDS;
}

int sem_init(char *name, int value) {
    int idx = get_new_sem();
    if(idx == OUT_OF_BOUNDS) {          // No more sems available
        return ERROR;
    }
    semaphores[idx].sem_id = idx*2+1;    // The ID will be odd
    semaphores[idx].open_count = 0;      // The sem has never been 'opened' yet
    semaphores[idx].value = value;
    semaphores[idx].blocked_first = 0;
    semaphores[idx].blocked_last = 0;
    semaphores[idx].lock = 0;

    my_strcpy(semaphores[idx].name, name);
    for(int i = 0; i < MAX_PROC; i++) {
        semaphores[idx].blocked_processes[i] = NO_PID;   // Later, the PIDs of the blocked processes will be here
    }
    return SUCCESS_SIGNAL;
}

int get_sem_by_name(char *name) {
    for(int idx = 0; idx < MAX_SEMS; idx++) {
        if(strcomp(semaphores[idx].name,name) == 0 && is_in_use(semaphores[idx].sem_id)) {
            return idx;
        }
    }
    return OUT_OF_BOUNDS;
}

void update_sem_processes(p_sem sem) {
    uint64_t idx;
    bool awake = true;
    while(sem->blocked_last - (idx = sem->blocked_first) > 0 || (awake = false)) {
        if(_cmpxchg(&sem->blocked_first, idx + 1, idx) == idx)
            break;
    }
    if(awake) {
        int pid = sem->blocked_processes[idx % MAX_PROC];  // First process blocked by sem
        set_process_state(pid, READY);                    // Unblock first process
    }
}