#include <concepts>
#include <print>
#include <string>

template <typename T>
concept StringRepresentable = requires(T a) { std::to_string(a); };

// Task: write the function without the template keyword
auto concat(StringRepresentable auto t1, StringRepresentable auto t2) {
    return std::to_string(t1) + std::to_string(t2);
}

int main(int argc, const char** argv) {
    auto ret = concat(2.2, 2.5);
    std::println("Result: {}", ret);
    std::println("{}", typeid(ret).name());  // Should print 12.5

    // This does not compile because std::string does not satisfy the
    // SatisfiesToString concept
    // ret = concat(1.2, "Hello");
    return 0;
}