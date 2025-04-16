#ifndef CPULOOP_H
#define CPULOOP_H

#include "Calibrator.h"
#include "Looper.h"
#include "timespec.h"

class CpuLoop {
private:
    Calibrator& calibrator;
    Looper looper;

public:
    CpuLoop(Calibrator& calibrator);
    double runTime(double duration_ms);
};

#endif