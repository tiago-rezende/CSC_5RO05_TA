#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <signal.h>
#include <iostream>

class Timer
{
private: 
    timer_t tid;

public:
    Timer();
    virtual ~Timer();
    void start(timespec duration, bool isPeriodic);
    void start_ms(double duration_ms, bool isPeriodic);
    void stop();

protected:
    virtual void callback() = 0;  
    
private:
    static void call_callback(int sig, siginfo_t* si, void*);
};

#endif 