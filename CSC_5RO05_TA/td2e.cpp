#include "CpuLoop.h"
#include "Calibrator.h"
#include <iostream>

int main() {
    Calibrator calibrator(2.0, 10);
    CpuLoop cpuLoop(calibrator);
    
    for (double duration_ms = 5; duration_ms <= 100; duration_ms += 2) {
        double error = cpuLoop.runTime(duration_ms);
        
        std::cout << "Requested: " << duration_ms << " ms | ";
        std::cout << "Error: " << error << "%";
        
        if (error > 10.0 || error < -10.0) {
            std::cout << " (OUT OF RANGE)";
        }
        std::cout << std::endl;
    }
    
    return 0;
}