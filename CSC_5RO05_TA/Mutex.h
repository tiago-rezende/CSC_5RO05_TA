//first implementation


// #ifndef MUTEX_H
// #define MUTEX_H

// #include <pthread.h>

// class Mutex {
// private:
//     pthread_mutex_t posixMutexId;
//     pthread_mutexattr_t posixMutexAttrId;
    
// public:
//     Mutex(bool isInversionSafe = false);
//     ~Mutex();
    
//     void lock();
//     bool lock(double timeout_ms);
//     void unlock();
    
//     class Lock {
//     private:
//         Mutex& mutex;
        
//     public:
//         Lock(Mutex& mutex) : mutex(mutex) { mutex.lock(); }
//         ~Lock() { mutex.unlock(); }
//     };
// };

// #endif 



//implementation of question 3e
#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex {
private:
    pthread_mutex_t posixId;
    pthread_mutexattr_t posixAttr;
    
public:
    Mutex(bool isInversionSafe = false);
    ~Mutex();
    
    void lock();
    void unlock();
    
    class Lock {
    public:
        Lock(Mutex& m);
        ~Lock();
    private:
        Mutex& mutex;
    };
};

#endif