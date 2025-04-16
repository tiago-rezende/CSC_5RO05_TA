#include "CpuLoop.h"
#include <time.h>

CpuLoop::CpuLoop(Calibrator& calibrator) : calibrator(calibrator) {}

double CpuLoop::runTime(double duration_ms) {
    double nLoops = calibrator.nLoops(duration_ms);
    
    timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    
    looper.runLoop(nLoops);
    
    clock_gettime(CLOCK_REALTIME, &end);
    
    timespec elapsed = timespec_subtract(end, start);
    double actual_ms = timespec_to_ms(elapsed);
    
    double error = (actual_ms - duration_ms) / duration_ms ;
    
    return error;
}