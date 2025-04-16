#include "timespec.h"

int k=1000;
int m=1000000;
int g=1000000000;

double timespec_to_ms(const timespec& time_ts)
{
    return time_ts.tv_sec*k+time_ts.tv_nsec/m;
}
timespec timespec_from_ms(double time_ms)
{
    timespec time_ts;
    time_ts.tv_sec = static_cast<time_t>(time_ms);
    double fractional = time_ms - time_ts.tv_sec;
    time_ts.tv_nsec = static_cast<long>((fractional * g) + (fractional >= 0 ? 0.5 : -0.5));

    if (time_ms<0)
    {
        time_ts.tv_nsec = time_ts.tv_nsec+g;
        time_ts.tv_sec =time_ts.tv_sec -1;//--;
    }
    return time_ts;
}


timespec timespec_now()
{
    timespec deadline;
    clock_gettime(CLOCK_REALTIME, &deadline);
    return deadline;
}

timespec timespec_negate(const timespec& time_ts)
{
    timespec time = time_ts;
    if (time_ts.tv_sec >= 0)
    {
        
        time.tv_nsec = - time_ts.tv_nsec+g;
        time.tv_sec = - time.tv_sec -1;
    }
    else
    {
        time.tv_nsec = - time_ts.tv_nsec+g;
        time.tv_sec = - time.tv_sec -1 ; 
    }
    return time;

}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
    timespec out;
    out.tv_nsec = time1_ts.tv_nsec+time2_ts.tv_nsec;
    out.tv_sec = static_cast<time_t>(out.tv_nsec/(g))+time1_ts.tv_sec+time2_ts.tv_sec;

    if(out.tv_nsec>=g)
    {
        out.tv_nsec+=-g;
        out.tv_sec = out.tv_sec;
    }

    return out;
        
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts){

   
    timespec time2_neg = timespec_negate(time2_ts);
    timespec out = timespec_add(time1_ts,time2_neg);


    return out;

}

void timespec_wait(const timespec& delay_ts)
{

    nanosleep(&delay_ts, NULL);

}

timespec  operator- (const timespec& time_ts)
{
    return timespec_negate(time_ts);
}

timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts){
    return  timespec_add(time1_ts, time2_ts);
}


timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)
{
    return  timespec_add(time1_ts, timespec_negate(time2_ts));
}




timespec& operator+= (timespec& time_ts, const timespec& delay_ts){
    time_ts = time_ts + delay_ts;
    return time_ts ;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts){
    time_ts = time_ts - delay_ts;
    return time_ts ;
}



bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
    if(time1_ts.tv_nsec == time2_ts.tv_nsec)
    {
        if(time1_ts.tv_sec == time2_ts.tv_sec)
        {
            return true;
        }
        return false;
    }  
    return false;
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
    if(time1_ts.tv_nsec == time2_ts.tv_nsec)
    {
        if(time1_ts.tv_sec == time2_ts.tv_sec)
        {
            return false;
        }
        return true;
    }  
    return true;
}


bool operator< (const timespec& time1_ts, const timespec& time2_ts){
    double time1, time2;
    time1 = timespec_to_ms(time1_ts);
    time2 = timespec_to_ms(time2_ts);
    if(time1<time2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts){
    double time1, time2;
    time1 = timespec_to_ms(time1_ts);
    time2 = timespec_to_ms(time2_ts);
    if(time1>time2)
    {
        return true;
    }
    else
    {
        return false;
    }
}