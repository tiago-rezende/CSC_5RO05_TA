#include <iostream>
#include <chrono>
#include "Looper.h"
#include "Chrono.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Use: " << argv[0] << " <nLoops>" << std::endl;
        return 1;
    }

    double nLoops = std::stod(argv[1]);

    Looper looper;

    Chrono chrono;

    chrono.restart();
    double result = looper.runLoop(nLoops);
    timespec elapsed = chrono.stop();

    std::cout << "nLoops: " << nLoops << std::endl;
    std::cout << "Execution time: " << timespec_to_ms(elapsed) / 1000.0 << " seconds" << std::endl;

    return 0;
}