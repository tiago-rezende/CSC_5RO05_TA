#include "Thread.h"
#include <time.h>

Thread::Thread(int id) : id(id), started(false) {
    pthread_attr_init(&posixThreadAttr);
}

Thread::~Thread() {
    if (started && !pthread_equal(posixThreadId, pthread_self())) {
        pthread_detach(posixThreadId);
    }
    pthread_attr_destroy(&posixThreadAttr);
}

void* Thread::call_run(void* v_thread) {
    Thread* thread = static_cast<Thread*>(v_thread);
    clock_gettime(CLOCK_REALTIME, &thread->startTime);
    thread->run();
    clock_gettime(CLOCK_REALTIME, &thread->endTime);
    return nullptr;
}

void Thread::start(int priority) {
    if (started) return;

    struct sched_param schedParam;
    schedParam.sched_priority = priority;
    pthread_attr_setschedparam(&posixThreadAttr, &schedParam);
    pthread_attr_setinheritsched(&posixThreadAttr, PTHREAD_EXPLICIT_SCHED);

    if (pthread_create(&posixThreadId, &posixThreadAttr, &Thread::call_run, this) != 0) {
        started = false;
        return;
    }

    started = true;
}

void Thread::join() {
    if (started) {
        clock_gettime(CLOCK_REALTIME, &endTime);
        pthread_join(posixThreadId, nullptr);
        started = false;
    }
}

bool Thread::isStarted() const {
    return started;
}

long Thread::duration_ms() const {
    if (!started) return 0;
    
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
    
    return (seconds * 1000) + (nanoseconds / 1000000);
}

void Thread::setMainSched(int policy) {
    struct sched_param param;
    param.sched_priority = (policy == SCHED_OTHER) ? 0 : sched_get_priority_max(policy);
    pthread_setschedparam(pthread_self(), policy, &param);
}

int Thread::getMainSched() {
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);
    return param.sched_priority;
}

int Thread::getMaxPrio(int policy) {
    return sched_get_priority_max(policy);
}

int Thread::getMinPrio(int policy) {
    return sched_get_priority_min(policy);
}