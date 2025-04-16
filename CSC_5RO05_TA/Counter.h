#ifndef COUNTER_H
#define COUNTER_H

#include "Mutex.h"

class Counter {
private:
    double m_value;
    Mutex* p_mutex;
    
    double incrProtect();
    double incrNoProtect();
    
    double (Counter::*incrementFunc)();

public:
    Counter(bool protect);
    ~Counter();
    
    double increment();
    double value() const;
    bool isProtected() const;
};

#endif