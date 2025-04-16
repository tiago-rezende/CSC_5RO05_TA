#ifndef TOKEN_PRODUCER_H
#define TOKEN_PRODUCER_H

#include "Thread.h"
#include "Semaphore.h"

class TokenProducer : public Thread {
private:
    Semaphore& sem;
    const Semaphore::CountType tokensToProduce;
    Semaphore::CountType tokensProduced;
    
public:
    TokenProducer(int id, Semaphore& s, Semaphore::CountType tokens);
    void run() override;
    Semaphore::CountType getTokensProduced() const;
};

#endif