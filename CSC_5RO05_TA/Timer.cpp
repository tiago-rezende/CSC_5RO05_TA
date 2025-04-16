#include "Timer.h"
#include "timespec.h"

Timer::Timer()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = call_callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = this;

    timer_create(CLOCK_REALTIME, &sev, &tid);
}

Timer::~Timer()
{
    timer_delete(tid);
}

void Timer::start(timespec duration, bool isPeriodic)
{
    itimerspec its{};
    
    if (isPeriodic)
    {
        its.it_value = duration;
        its.it_interval = duration;
    }
    else
    {
        its.it_value = duration;
        its.it_interval = {0, 0};
    }
    
    timer_settime(tid, 0, &its, nullptr);
}

void Timer::start_ms(double duration_ms, bool isPeriodic)
{
    timespec duration_timespec = timespec_from_ms(duration_ms);
    start(duration_timespec, isPeriodic);
}

void Timer::stop()
{
    itimerspec zero{};
    zero.it_value.tv_sec = 0;
    zero.it_value.tv_nsec = 0;
    zero.it_interval.tv_sec = 0;
    zero.it_interval.tv_nsec = 0;
    timer_settime(tid, 0, &zero, nullptr);
}

void Timer::call_callback(int /*sig*/, siginfo_t* si, void* /*unused*/)
{
    Timer* p_timer = static_cast<Timer*>(si->si_value.sival_ptr);
    p_timer->callback();
}