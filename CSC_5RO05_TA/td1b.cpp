#include <iostream>
#include "Chrono.h"
#include "timespec.h"

int main() {
    Chrono chrono;
    
    std::cout << "Starting chronometer..." << std::endl;
    timespec_wait(timespec_from_ms(1.5)); 
    std::cout << "Lap time: " << chrono.lap_ms() << " ms" << std::endl;
    
    timespec_wait(timespec_from_ms(0.5)); 
    std::cout << "Stopping chronometer..." << std::endl;
    timespec duration = chrono.stop();
    
    std::cout << "Total time: " << timespec_to_ms(duration) << " ms" << std::endl;
    std::cout << "Lap after stop: " << chrono.lap_ms() << " ms" << std::endl;
    
    std::cout << "Restarting..." << std::endl;
    chrono.restart();
    timespec_wait(timespec_from_ms(1)); 
    std::cout << "New lap: " << chrono.lap_ms() << " ms" << std::endl;
    
    return 0;
}