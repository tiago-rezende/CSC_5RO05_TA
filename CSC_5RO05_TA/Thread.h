#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread {
private:
    pthread_t posixThreadId;
    pthread_attr_t posixThreadAttr;
    const int id;
    bool started;
    struct timespec startTime;
    struct timespec endTime;

    static void* call_run(void* v_thread);

public:
    Thread(int id);
    virtual ~Thread();

    void start(int priority = 0);
    void join();
    bool isStarted() const;
    long duration_ms() const;

    virtual void run() = 0;  

    static void setMainSched(int policy);
    static int getMainSched();
    static int getMaxPrio(int policy);
    static int getMinPrio(int policy);
};

#endif