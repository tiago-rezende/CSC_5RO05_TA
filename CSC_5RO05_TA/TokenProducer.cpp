#include "TokenProducer.h"

TokenProducer::TokenProducer(int id, Semaphore& s, Semaphore::CountType tokens)
    : Thread(id), sem(s), tokensToProduce(tokens), tokensProduced(0) {}

void TokenProducer::run() {
    for (Semaphore::CountType i = 0; i < tokensToProduce; i++) {
        sem.give();
        tokensProduced++;
    }
}

Semaphore::CountType TokenProducer::getTokensProduced() const {
    return tokensProduced;
}