#include "Semaphore.h"

#ifndef ETIMEDOUT
#define ETIMEDOUT 110 
#endif

Semaphore::Semaphore(CountType initValue, CountType maxValue) 
    : mutex(), monitor(mutex), counter(initValue), maxCount(maxValue) {}

void Semaphore::give() {
    Monitor::Lock lock(monitor);
    if (counter < maxCount) {
        counter++;
        monitor.notify();
    }
}

void Semaphore::take() {
    Monitor::Lock lock(monitor);
    while (counter == 0) {
        lock.wait();
    }
    counter--;
}

bool Semaphore::take(long timeout_ms) {
    Monitor::Lock lock(monitor);
    if (counter == 0) {
        struct timespec start, current;
        clock_gettime(CLOCK_REALTIME, &start);
        
        while (counter == 0) {
            clock_gettime(CLOCK_REALTIME, &current);
            long elapsed_ms = (current.tv_sec - start.tv_sec) * 1000 +
                            (current.tv_nsec - start.tv_nsec) / 1000000;
            
            if (elapsed_ms >= timeout_ms) {
                return false;  
            }
            
            struct timespec ts;
            ts.tv_sec = 0;
            ts.tv_nsec = 10000000; 
            nanosleep(&ts, NULL);
            
        }
    }
    counter--;
    return true;
}