#ifndef MUTEX_H
#define MUTEX_H

    typedef struct mutex {
        
    } mutex_t;

    mutex_t * makeMutex();
    void mutexLock(mutex_t * m);
    void mutexUnlock(mutex_t * m);

#endif