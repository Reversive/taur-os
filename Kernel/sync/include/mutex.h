#ifndef MUTEX_H
#define MUTEX_H

    typedef struct mutex {
        
    } mutex_t;

    mutex * makeMutex();
    void mutexLock(mutex * m);
    void mutexUnlock(mutex * m);

#endif