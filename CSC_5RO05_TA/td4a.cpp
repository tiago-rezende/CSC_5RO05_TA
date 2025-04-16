#include "Monitor.h"
#include <iostream>

Mutex mutex;
Monitor monitor(mutex);
bool condition = false;
int shared_value = 0;

void* producer(void*) {
    Monitor::Lock lock(monitor);
    shared_value = 42;
    condition = true;
    monitor.notify();
    return nullptr;
}

void* consumer(void*) {
    Monitor::Lock lock(monitor);
    while (!condition) {
        lock.wait();
    }
    std::cout << "Consumed value: " << shared_value << std::endl;
    return nullptr;
}

int main() {
    pthread_t prod, cons;
    
    pthread_create(&cons, nullptr, consumer, nullptr);
    
    struct timespec ts = {0, 100000000}; 
    nanosleep(&ts, nullptr);
    
    pthread_create(&prod, nullptr, producer, nullptr);
    
    pthread_join(prod, nullptr);
    pthread_join(cons, nullptr);
    
    return 0;
}