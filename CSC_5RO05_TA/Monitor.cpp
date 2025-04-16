#include "Monitor.h"

Monitor::Monitor(Mutex& m) : mutex(m) {
    pthread_cond_init(&posixCondId, nullptr);
}

Monitor::~Monitor() {
    pthread_cond_destroy(&posixCondId);
}

void Monitor::notify() {
    pthread_cond_signal(&posixCondId);
}

void Monitor::notifyAll() {
    pthread_cond_broadcast(&posixCondId);
}

Monitor::Lock::Lock(Monitor& m) 
    : Mutex::Lock(m.mutex), monitor(m) {}

void Monitor::Lock::wait() {
    pthread_cond_wait(&monitor.posixCondId, (pthread_mutex_t*)&monitor.mutex);
}