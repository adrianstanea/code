#include <print>
#include <string>

#include "KeyValuePair.h"

// Adaptation for a specialized class template instantiation where const char* keys and values are converted to std::string

int main(int argc, const char** argv) {
    KeyValuePair<std::string, int> pair{"Age", 30};
    std::println("Key: {}, Value: {}", pair.getKey(), pair.getValue());

    // This should use the specialized constructor
    auto pair2{KeyValuePair{"Age123124", "ABC"}};
    std::println("Key: {}, Value: {}", pair2.getKey(), pair2.getValue());

    // CTAD: class template argument deduction -> the compiler infers the types
    // based on the constructor arguments
    using namespace std::string_literals;
    KeyValuePair pair3{"Me"s, 24};
    std::println("Key: {}, Value: {}", pair3.getKey(), pair3.getValue());

    return 0;
}