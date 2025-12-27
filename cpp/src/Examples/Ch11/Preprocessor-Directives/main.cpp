#include <print>

#define SQUARE(x) ((x) * (x))

int main(int argc, const char** argv) {
    std::println("{}", SQUARE(5));
    return 0;
}