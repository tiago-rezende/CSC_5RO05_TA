#include "Counter.h"
#include "Incrementer.h"
#include <iostream>

int main() {
    Counter protectedCounter(true);
    Counter unprotectedCounter(false);
    
    Incrementer inc1(1, protectedCounter, 1000000);
    Incrementer inc2(2, protectedCounter, 1000000);
    
    inc1.start();
    inc2.start();
    
    inc1.join();
    inc2.join();
    
    std::cout << "Protected counter value: " << protectedCounter.value() << std::endl;
    
    Incrementer inc3(3, unprotectedCounter, 1000000);
    Incrementer inc4(4, unprotectedCounter, 1000000);
    
    inc3.start();
    inc4.start();
    
    inc3.join();
    inc4.join();
    
    std::cout << "Unprotected counter value: " << unprotectedCounter.value() << std::endl;
    
    return 0;
}