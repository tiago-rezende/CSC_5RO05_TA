#include "Semaphore.h"
#include "TokenProducer.h"
#include "TokenConsumer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] 
                  << " <num_consumers> <num_producers> <tokens_per_producer>" << std::endl;
        return 1;
    }

    int numConsumers = 0;
    for (char* p = argv[1]; *p; p++) numConsumers = numConsumers * 10 + (*p - '0');
    
    int numProducers = 0;
    for (char* p = argv[2]; *p; p++) numProducers = numProducers * 10 + (*p - '0');
    
    Semaphore::CountType tokensPerProducer = 0;
    for (char* p = argv[3]; *p; p++) tokensPerProducer = tokensPerProducer * 10 + (*p - '0');

    Semaphore sem;

    TokenConsumer** consumers = new TokenConsumer*[numConsumers];
    TokenProducer** producers = new TokenProducer*[numProducers];

    for (int i = 0; i < numConsumers; i++) {
        consumers[i] = new TokenConsumer(i, sem);
    }

    for (int i = 0; i < numProducers; i++) {
        producers[i] = new TokenProducer(i, sem, tokensPerProducer);
    }

    for (int i = 0; i < numConsumers; i++) {
        consumers[i]->start();
    }

    for (int i = 0; i < numProducers; i++) {
        producers[i]->start();
    }

    for (int i = 0; i < numProducers; i++) {
        producers[i]->join();
    }

    for (int i = 0; i < numConsumers; i++) {
        consumers[i]->join();
    }

    Semaphore::CountType totalProduced = 0;
    Semaphore::CountType totalConsumed = 0;

    for (int i = 0; i < numProducers; i++) {
        totalProduced += producers[i]->getTokensProduced();
        delete producers[i];
    }

    for (int i = 0; i < numConsumers; i++) {
        totalConsumed += consumers[i]->getTokensConsumed();
        delete consumers[i];
    }

    delete[] consumers;
    delete[] producers;

    std::cout << "Total tokens produced: " << totalProduced << std::endl;
    std::cout << "Total tokens consumed: " << totalConsumed << std::endl;
    std::cout << "Tokens lost: " << (totalProduced - totalConsumed) << std::endl;

    return 0;
}