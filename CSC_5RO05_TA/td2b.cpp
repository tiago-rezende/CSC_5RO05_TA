#include "Timer.h"
#include <iostream>
#include <unistd.h>

class CountDown : public Timer
{
private:
    int count;
    
protected:
    void callback() override
    {
        std::cout << count << std::endl;
        if (count-- <= 0)
        {
            stop();
        }
    }
    
public:
    CountDown(int n) : count(n) {}
};

int main()
{
    CountDown countdown(10); 
    countdown.start_ms(1, true);
    
    while(true)
    {
        pause(); 
    }
    
    return 0;
}