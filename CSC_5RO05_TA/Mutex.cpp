//first implementation

// #include "Mutex.h"
// #include <time.h>

// Mutex::Mutex(bool isInversionSafe) {
//     pthread_mutexattr_init(&posixMutexAttrId);
    
//     if (isInversionSafe) {
//         pthread_mutexattr_settype(&posixMutexAttrId, PTHREAD_MUTEX_RECURSIVE);
//         pthread_mutexattr_setprotocol(&posixMutexAttrId, PTHREAD_PRIO_INHERIT);
//     }
    
//     pthread_mutex_init(&posixMutexId, &posixMutexAttrId);
//     pthread_mutexattr_destroy(&posixMutexAttrId);
// }

// Mutex::~Mutex() {
//     pthread_mutex_destroy(&posixMutexId);
// }

// void Mutex::lock() {
//     pthread_mutex_lock(&posixMutexId);
// }

// bool Mutex::lock(double timeout_ms) {
//     struct timespec deadline;
//     clock_gettime(CLOCK_REALTIME, &deadline);
    
//     long sec = static_cast<long>(timeout_ms / 1000);
//     long nsec = static_cast<long>((timeout_ms - sec * 1000) * 1000000);
    
//     deadline.tv_sec += sec;
//     deadline.tv_nsec += nsec;
    
//     if (deadline.tv_nsec >= 1000000000) {
//         deadline.tv_sec += 1;
//         deadline.tv_nsec -= 1000000000;
//     }
    
//     return pthread_mutex_timedlock(&posixMutexId, &deadline) == 0;
// }

// void Mutex::unlock() {
//     pthread_mutex_unlock(&posixMutexId);
// }


//implementation of question 3e


#include "Mutex.h"

Mutex::Mutex(bool isInversionSafe) {
    pthread_mutexattr_init(&posixAttr);
    
    if (isInversionSafe) {
        pthread_mutexattr_settype(&posixAttr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutexattr_setprotocol(&posixAttr, PTHREAD_PRIO_INHERIT);
    }
    
    pthread_mutex_init(&posixId, &posixAttr);
    pthread_mutexattr_destroy(&posixAttr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&posixId);
}

void Mutex::lock() {
    pthread_mutex_lock(&posixId);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&posixId);
}

Mutex::Lock::Lock(Mutex& m) : mutex(m) {
    mutex.lock();
}

Mutex::Lock::~Lock() {
    mutex.unlock();
}