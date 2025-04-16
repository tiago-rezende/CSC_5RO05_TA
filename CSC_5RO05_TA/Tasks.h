#ifndef TASKS_HPP
#define TASKS_HPP

#include "Thread.h"
#include "Mutex.h"
#include "CpuLoop.h"

extern Mutex resource;
extern Calibrator calibrator;

class Thread_A : public Thread {
private:
    CpuLoop cpuLoop;
    
public:
    Thread_A(int id) : Thread(id), cpuLoop(calibrator) {}
    
    void run() override {
        Mutex::Lock lock(resource);
        for (int i = 0; i < 1; i++) {
            cpuLoop.runLoop(); 
        }
    }
};

class Thread_B : public Thread {
private:
    CpuLoop cpuLoop;
    
public:
    Thread_B(int id) : Thread(id), cpuLoop(calibrator) {}
    
    void run() override {
        
        for (int i = 0; i < 10; i++) {
            cpuLoop.runLoop();
        }
    }
};

class Thread_C : public Thread {
private:
    CpuLoop cpuLoop;
    
public:
    Thread_C(int id) : Thread(id), cpuLoop(calibrator) {}
    
    void run() override {
        Mutex::Lock lock(resource);
        
        for (int i = 0; i < 100; i++) {
            cpuLoop.runLoop();
        }
    }
};

#endif 