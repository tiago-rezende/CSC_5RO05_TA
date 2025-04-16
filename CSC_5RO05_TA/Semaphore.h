#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "Monitor.h"

class Semaphore {
public:
    using CountType = unsigned long;
    
private:
    Mutex mutex; 
    Monitor monitor;
    CountType counter;
    CountType maxCount;

public:
    Semaphore(CountType initValue = 0, CountType maxValue = ~0UL);
    
    void give();
    void take();
    bool take(long timeout_ms);
};

#endif