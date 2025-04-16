#include "timespec.h"
#include <iostream>

int main() {
    double test_pos = 2.7;
    double test_neg = -2.7;

    timespec tsp = timespec_from_ms(test_pos * 1000);
    timespec tsn = timespec_from_ms(test_neg * 1000);

    std::cout << "Test 1: Conversion from double to timespec\n";
    std::cout << "Input: " << test_pos << " s -> timespec: sec = " << tsp.tv_sec << ", nsec = " << tsp.tv_nsec << "\n";
    std::cout << "Input: " << test_neg << " s -> timespec: sec = " << tsn.tv_sec << ", nsec = " << tsn.tv_nsec << "\n\n";

    double back_to_ms_pos = timespec_to_ms(tsp) / 1000;
    double back_to_ms_neg = timespec_to_ms(tsn) / 1000;

    std::cout << "Test 2: Conversion from timespec to double\n";
    std::cout << "timespec: sec = " << tsp.tv_sec << ", nsec = " << tsp.tv_nsec << " -> Output: " << std::fixed << back_to_ms_pos << " s\n";
    std::cout << "timespec: sec = " << tsn.tv_sec << ", nsec = " << tsn.tv_nsec << " -> Output: " << std::fixed << back_to_ms_neg << " s\n\n";

    timespec now = timespec_now();
    std::cout << "Test 3: Current time\n";
    std::cout << "Current time: sec = " << now.tv_sec << ", nsec = " << now.tv_nsec << "\n\n";

    timespec neg_now = timespec_negate(now);
    std::cout << "Test 4: Negation of timespec\n";
    std::cout << "Negated current time: sec = " << neg_now.tv_sec << ", nsec = " << neg_now.tv_nsec << "\n\n";

    timespec sum = tsp + tsn;
    timespec diff = tsp - tsn;
    timespec result = tsp;
    result += tsn;
    timespec result2 = tsp;
    result2 -= tsn;

    std::cout << "Test 5: Arithmetic operations\n";
    std::cout << "tsp + tsn: sec = " << sum.tv_sec << ", nsec = " << sum.tv_nsec << "\n";
    std::cout << "tsp - tsn: sec = " << diff.tv_sec << ", nsec = " << diff.tv_nsec << "\n";
    std::cout << "tsp += tsn: sec = " << result.tv_sec << ", nsec = " << result.tv_nsec << "\n";
    std::cout << "tsp -= tsn: sec = " << result2.tv_sec << ", nsec = " << result2.tv_nsec << "\n\n";

    std::cout << "Test 6: Comparisons\n";
    std::cout << "tsp == tsn: " << (tsp == tsn ? "true" : "false") << "\n";
    std::cout << "tsp != tsn: " << (tsp != tsn ? "true" : "false") << "\n";
    std::cout << "tsp < tsn: " << (tsp < tsn ? "true" : "false") << "\n";
    std::cout << "tsp > tsn: " << (tsp > tsn ? "true" : "false") << "\n\n";

    std::cout << "Test 7: Wait for 2 seconds\n";
    timespec wait_time = {2, 0};
    std::cout << "Starting wait...\n";
    timespec_wait(wait_time);
    std::cout << "Wait completed.\n";

    return 0;
}