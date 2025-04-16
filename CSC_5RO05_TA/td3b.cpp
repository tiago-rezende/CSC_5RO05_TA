#include <pthread.h>
#include <iostream>
#include "Mutex.h"

struct SharedData {
    volatile bool stop;
    double counter;
    Mutex mutex;
};

void* incrementer(void* v_data) {
    SharedData* data = (SharedData*) v_data;
    while (true) {
        {
            Mutex::Lock lock(data->mutex); 
            if (data->stop) break;
            data->counter += 1.0;
        }
    }
    
    {
        Mutex::Lock lock(data->mutex);
        std::cout << "Counter value = " << data->counter << std::endl;
    }
    return v_data;
}

int main() {
    SharedData data;
    data.stop = false;
    data.counter = 0.0;
    
    pthread_t incrementThread;
    pthread_create(&incrementThread, nullptr, incrementer, (void*) &data);
    
    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd) {
        std::cout << "Type 's' to stop: " << std::flush;
    }
    
    {
        Mutex::Lock lock(data.mutex);
        data.stop = true;
    }
    
    pthread_join(incrementThread, nullptr);
    return 0;
}