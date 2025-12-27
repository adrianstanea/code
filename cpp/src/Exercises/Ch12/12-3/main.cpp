#include <print>
#include <string>

#include "KeyValuePair.h"

int main(int argc, const char** argv) {
    KeyValuePair pair{0, 3.14};
    std::println("Key: {}, Value: {}", pair.getKey(), pair.getValue());

    // This will not compile because of the concept constraints - first template
    // parameter must be integral, second must be floating point KeyValuePair
    // pair2{"Hello", 123.4};

    return 0;
}