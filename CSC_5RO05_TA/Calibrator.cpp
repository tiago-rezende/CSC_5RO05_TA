#include "Calibrator.h"
#include "Chrono.h"
#include <iostream>
#include <cmath>

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples) 
    : samplingPeriod_ms(samplingPeriod_ms), nSamples(nSamples) {
    start_ms(samplingPeriod_ms, true);
    looper.runLoop(1.0e300);  
}

void Calibrator::callback() {
    if (samples.size() < nSamples) {
        samples.push_back(looper.getSample());
        
        if (samples.size() == nSamples) {
            stop();
            looper.stopLoop();
            computeRegression();
        }
    }
}

void Calibrator::computeRegression() {
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_xx = 0.0;
    const size_t n = samples.size();
    
    for (size_t i = 0; i < n; ++i) {
        double x = i * samplingPeriod_ms;
        double y = samples[i];
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_xx += x * x;
    }
    
    double denominator = n * sum_xx - sum_x * sum_x;
    if (fabs(denominator) > 1e-10) {  
        a = (n * sum_xy - sum_x * sum_y) / denominator;
        b = (sum_y * sum_xx - sum_x * sum_xy) / denominator;
    } else {
        a = 0.0;
        b = 0.0;
    }
}

double Calibrator::nLoops(double duration_ms) const {
    return a * duration_ms + b;
}