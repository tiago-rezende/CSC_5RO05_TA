// #include "Incrementer.h"

// Incrementer::Incrementer(int id, Counter& counter, double nLoops)
//     : Thread(id), counter(counter), nLoops(nLoops) {}

// void Incrementer::run() {
//     for (double i = 0; i < nLoops; i++) {
//         counter.increment();
//     }
// }

#include "Incrementer.h"

Incrementer::Incrementer(int id, Counter& counter, double nLoops)
    : Thread(id), counter(counter), nLoops(nLoops) {}

void Incrementer::run() {
    for (double i = 0; i < nLoops; i++) {
        counter.increment();
    }
}