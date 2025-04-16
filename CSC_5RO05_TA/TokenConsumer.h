#ifndef TOKEN_CONSUMER_H
#define TOKEN_CONSUMER_H

#include "Thread.h"
#include "Semaphore.h"

class TokenConsumer : public Thread {
private:
    Semaphore& sem;
    Semaphore::CountType tokensConsumed;
    
public:
    TokenConsumer(int id, Semaphore& s);
    void run() override;
    Semaphore::CountType getTokensConsumed() const;
};

#endif