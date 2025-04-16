#include "Incrementer.h"
#include "Counter.h"
#include "Chrono.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] 
                  << " <nLoops> <nTasks> [protect] [policy]" << std::endl;
        return 1;
    }

    double nLoops = 0;
    for (char* p = argv[1]; *p; p++) nLoops = nLoops * 10 + (*p - '0');
    
    int nTasks = 0;
    for (char* p = argv[2]; *p; p++) nTasks = nTasks * 10 + (*p - '0');

    bool protect = false;
    if (argc > 3) protect = (argv[3][0] != '0');

    int policy = SCHED_OTHER;
    if (argc > 4) {
        if (argv[4][0] == 'R') policy = SCHED_RR;
        else if (argv[4][0] == 'F') policy = SCHED_FIFO;
    }

    Thread::setMainSched(policy);

    Counter counter(protect);

    Chrono chrono;
    Incrementer** incrementers = new Incrementer*[nTasks];
    pthread_t* threads = new pthread_t[nTasks];

    chrono.restart();
    for (int i = 0; i < nTasks; i++) {
        incrementers[i] = new Incrementer(i, counter, nLoops);
        incrementers[i]->start(Thread::getMinPrio(policy) + 
                             (i % (Thread::getMaxPrio(policy) - Thread::getMinPrio(policy))));
    }

    for (int i = 0; i < nTasks; i++) {
        incrementers[i]->join();
        std::cout << "Task " << i << " duration: " 
                  << incrementers[i]->duration_ms() << " ms" << std::endl;
        delete incrementers[i];
    }

    double totalTime = chrono.lap_ms() / 1000.0;

    double expected = nLoops * nTasks;
    double actual = counter.value();
    double percentage = (actual / expected) * 100;

    std::cout << "Expected value: " << expected << std::endl;
    std::cout << "Actual value: " << actual << std::endl;
    std::cout << "Percentage: " << percentage << "%" << std::endl;
    std::cout << "Total execution time: " << totalTime << " s" << std::endl;

    delete[] incrementers;
    delete[] threads;

    return 0;
}