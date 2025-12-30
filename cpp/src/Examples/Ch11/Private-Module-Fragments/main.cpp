#include <math.h>  // For ::sqrt

import std;
import adder;

int main() {
    std::println("This should work");
    std::println(TEST_MACRO);

    Adder adder{};
    auto result = adder.add(1, 2);
    std::println("1 + 2 = {}", result);

    auto result_sqrt{::sqrt(4)};
    std::println("sqrt(4) = {}", result_sqrt);

    auto result_std_srqt{std::sqrt(4)};
    std::println("std::sqrt(4) = {}", result_std_srqt);

    return 0;
}
