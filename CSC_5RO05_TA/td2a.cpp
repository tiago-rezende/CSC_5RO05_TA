#include <time.h>
#include <signal.h>
#include <iostream>



void myHandler(int, siginfo_t* si, void*)
{
    int* p_counter = (int*)si -> si_value.sival_ptr;
    *p_counter +=1;
    printf("%d\n",*p_counter);
}



int main()
{
    
    volatile int counter = 0;
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void*) &counter;

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 500000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 500000000;
    
    timer_settime(tid, 0, &its, nullptr);
    while (counter<15){

    }

}