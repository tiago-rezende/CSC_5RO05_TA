#ifndef LOOPER_H
#define LOOPER_H

class Looper {
private:
    bool dostop;    
    double iLoop;   

public:
    Looper();

    double runLoop(double nLoops);

    double getSample() const;

    void stopLoop();
};

#endif 