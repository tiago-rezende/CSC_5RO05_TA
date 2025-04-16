#ifndef MONITOR_H
#define MONITOR_H

#include "Mutex.h"
#include <pthread.h>

class Monitor {
private:
    pthread_cond_t posixCondId;
    Mutex& mutex;

public:
    explicit Monitor(Mutex& m);
    ~Monitor();
    
    void notify();
    void notifyAll();

    class Lock : public Mutex::Lock {
    private:
        Monitor& monitor;
        
    public:
        Lock(Monitor& m);
        void wait();
    };
};

#endif