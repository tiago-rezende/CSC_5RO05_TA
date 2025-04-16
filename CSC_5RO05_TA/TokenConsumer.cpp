#include "TokenConsumer.h"

TokenConsumer::TokenConsumer(int id, Semaphore& s)
    : Thread(id), sem(s), tokensConsumed(0) {}

void TokenConsumer::run() {
    while (sem.take(500)) {  
        tokensConsumed++;
    }
}

Semaphore::CountType TokenConsumer::getTokensConsumed() const {
    return tokensConsumed;
}