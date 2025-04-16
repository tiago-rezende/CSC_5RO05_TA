#include <pthread.h>
#include <iostream>

struct Data {
    volatile bool stop;
    volatile double counter;
    pthread_mutex_t mutex;
};

void* incrementer(void* v_data) {
    Data* p_data = (Data*) v_data;
    while (!p_data->stop) {
        pthread_mutex_lock(&p_data->mutex);
        p_data->counter += 1.0;
        pthread_mutex_unlock(&p_data->mutex);
    }
    return v_data;
}

int main() {
    Data data;
    data.stop = false;
    data.counter = 0.0;
    pthread_mutex_init(&data.mutex, nullptr);
    
    pthread_t incrementThread[3];
    for (int i = 0; i < 3; ++i) {
        pthread_create(&incrementThread[i], nullptr, incrementer, &data);
    }

    std::cout << "Type 's' to stop: " << std::flush;
    char cmd;
    while (std::cin >> cmd && cmd != 's') {
        std::cout << "Type 's' to stop: " << std::flush;
    }
    
    data.stop = true;
    
    for (int i = 0; i < 3; ++i) {
        pthread_join(incrementThread[i], nullptr);
    }
    
    pthread_mutex_destroy(&data.mutex);
    std::cout << "Counter value = " << data.counter << std::endl;
    
    return 0;
}