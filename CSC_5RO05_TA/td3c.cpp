#include "Thread.h"
#include <iostream>

class IncrementerThread : public Thread {
private:
    volatile bool& stop;
    double counter;
    
public:
    IncrementerThread(int id, volatile bool& stop) 
        : Thread(id), stop(stop), counter(0.0) {}
        
    void run() override {
        while (!stop) {
            counter += 1.0;
        }
        std::cout << "Counter value = " << counter << std::endl;
    }
};

int main() {
    Thread::setMainSched(SCHED_OTHER);
    
    volatile bool stop = false;
    IncrementerThread incrementThread(1, stop);
    incrementThread.start();
    
    std::cout << "Type 's' to stop: " << std::flush;
    char cmd;
    while (std::cin >> cmd && cmd != 's') {
        std::cout << "Type 's' to stop: " << std::flush;
    }
    
    stop = true;
    incrementThread.join();
    
    std::cout << "Execution time: " << incrementThread.duration_ms() << " ms" << std::endl;
    
    return 0;
}