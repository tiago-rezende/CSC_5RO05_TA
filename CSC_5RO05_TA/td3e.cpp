#include "Thread.h"
#include "Mutex.h"
#include "CpuLoop.h"
#include "Calibrator.h"
#include "Chrono.h"
#include <iostream>

class Thread_A : public Thread {
private:
    Mutex& resource;
    double cpuTimeMs;
    Calibrator& calibrator;
    
public:
    Thread_A(int id, Mutex& res, Calibrator& calib, double timeMs) 
        : Thread(id), resource(res), calibrator(calib), cpuTimeMs(timeMs) {}
    
    void run() override {
        CpuLoop cpuLoop(calibrator);
        Mutex::Lock lock(resource);
        cpuLoop.runTime(cpuTimeMs);
    }
};

class Thread_B : public Thread {
private:
    Mutex& resource;
    double cpuTimeMs;
    Calibrator& calibrator;
    
public:
    Thread_B(int id, Mutex& res, Calibrator& calib, double timeMs) 
        : Thread(id), resource(res), calibrator(calib), cpuTimeMs(timeMs) {}
    
    void run() override {
        CpuLoop cpuLoop(calibrator);
        cpuLoop.runTime(cpuTimeMs);
    }
};

class Thread_C : public Thread {
private:
    Mutex& resource;
    double cpuTimeMs;
    Calibrator& calibrator;
    
public:
    Thread_C(int id, Mutex& res, Calibrator& calib, double timeMs) 
        : Thread(id), resource(res), calibrator(calib), cpuTimeMs(timeMs) {}
    
    void run() override {
        CpuLoop cpuLoop(calibrator);
        {
            Mutex::Lock lock(resource);
            cpuLoop.runTime(cpuTimeMs);
        }
        cpuLoop.runTime(cpuTimeMs);
    }
};

void millisleep(unsigned ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

int main() {
    
    Calibrator calibrator(200.0, 10);
    
    std::cout << "=== Unprotected Mode (Priority Inversion) ===" << std::endl;
    {
        Mutex resource(false);
        Chrono chrono;
        
        Thread_C task_C(1, resource, calibrator, 10.0);
        Thread_B task_B(2, resource, calibrator, 20.0);
        Thread_A task_A(3, resource, calibrator, 10.0);
        
        task_C.start(10);
        millisleep(1); 
        task_B.start(30);
        millisleep(1);
        task_A.start(50);
        
        task_A.join();
        task_B.join();
        task_C.join();
        
        std::cout << "Execution times:" << std::endl;
        std::cout << "Task A (High): " << task_A.duration_ms() << " ms" << std::endl;
        std::cout << "Task B (Medium): " << task_B.duration_ms() << " ms" << std::endl;
        std::cout << "Task C (Low): " << task_C.duration_ms() << " ms" << std::endl;
    }
    
    std::cout << "\n=== Protected Mode (Priority Inheritance) ===" << std::endl;
    {
        Mutex resource(true);
        Chrono chrono;
        
        Thread_C task_C(1, resource, calibrator, 10.0);
        Thread_B task_B(2, resource, calibrator, 20.0);
        Thread_A task_A(3, resource, calibrator, 10.0);
        
        task_C.start(10);
        millisleep(1);
        task_B.start(30);
        millisleep(1);
        task_A.start(50);
        
        task_A.join();
        task_B.join();
        task_C.join();
        
        std::cout << "Execution times:" << std::endl;
        std::cout << "Task A (High): " << task_A.duration_ms() << " ms" << std::endl;
        std::cout << "Task B (Medium): " << task_B.duration_ms() << " ms" << std::endl;
        std::cout << "Task C (Low): " << task_C.duration_ms() << " ms" << std::endl;
    }
    
    return 0;
}