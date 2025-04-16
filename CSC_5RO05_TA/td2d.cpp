#include "Calibrator.h"
#include "Chrono.h"
#include <iostream>

int main() {
    Calibrator calibrator(2, 10);
    
    for (double duration_ms = 5; duration_ms <= 100; duration_ms += 2) {
        Chrono chrono;
        chrono.restart();
        
        double predicted = calibrator.nLoops(duration_ms);
        Looper testLooper;
        testLooper.runLoop(predicted);
        
        timespec elapsed = chrono.stop();
        double actual_ms = elapsed.tv_sec * 1000.0 + elapsed.tv_nsec / 1000000.0;
        
        std::cout << "Requested: " << duration_ms << " ms | "
                  << "Actual: " << actual_ms << " ms | "
                  << "Error: " << (actual_ms - duration_ms) << " ms" << std::endl;
    }
    
    return 0;
}