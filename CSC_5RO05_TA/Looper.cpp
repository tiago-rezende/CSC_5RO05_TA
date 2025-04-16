#include "Looper.h"
#include <signal.h>
#include <iostream>

Looper::Looper() : dostop(false), iLoop(0.0) {
    std::cout << "Looper created. dostop = false, iLoop = 0.0" << std::endl;
}

double Looper::runLoop(double nLoops) {
    iLoop = 0.0;
    
    struct sigaction sa;
    sa.sa_handler = [](int){};
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, nullptr);

    while (iLoop < nLoops && !dostop) {
        iLoop += 1.0;
        sigset_t pending;
        sigpending(&pending);
        if (sigismember(&pending, SIGINT)) {
            dostop = true;
        }
    }

    return iLoop;
}

double Looper::getSample() const {
    std::cout << "getSample called. present iLoop = " << iLoop << std::endl;
    return iLoop;
}

void Looper::stopLoop() {
    std::cout << "stopLoop called. dostop defined as true" << std::endl;
    dostop = true;
}