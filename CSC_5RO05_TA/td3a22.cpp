#include <pthread.h>
#include <iostream>


struct Data {
    volatile bool stop;
    volatile double counter;
};

void* incrementer(void* v_data) {
    Data* p_data = (Data*) v_data;
    while (not p_data->stop) {
    p_data->counter += 1.0;
    }
    return v_data;
    }



int main()
{    
    Data data = { false, 0.0 };
    pthread_t incrementThread[1];
    pthread_create(&incrementThread[0], nullptr, incrementer, &data);
    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
        std::cout << "Type 's' to stop: " << std::flush;
    data.stop = true;
    for (int i=0; i<1; ++i) pthread_join(incrementThread[i], nullptr);
    std::cout << "Counter value = " << data.counter << std::endl;
        
}