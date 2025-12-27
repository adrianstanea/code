#include <concepts>
#include <print>
#include <string>

template <typename T>
concept StringRepresentable = requires(T a) { std::to_string(a); } ||
                              std::constructible_from<std::string, T>;

// Task: write the function without the template keyword
auto concat(StringRepresentable auto t1, StringRepresentable auto t2) {
    auto to_string_impl = [](auto&& t) {
        // constexpr is used here to enable compile-time branching -> only valid
        // paths are compiled for each type
        if constexpr (requires { std::to_string(t); }) {
            return std::to_string(t);
        } else {
            return std::string(t);
        }
    };
    return to_string_impl(t1) + to_string_impl(t2);
}

int main(int argc, const char** argv) {
    auto ret = concat(2.2, 2.5);
    std::println("Result: {}", ret);
    std::println("{}", typeid(ret).name());  // Should print 12.5

    // This does not compile because std::string does not satisfy the
    // SatisfiesToString concept
    using namespace std::string_literals;

    ret = concat(1.2, "Hello"s);
    std::println("Result: {}", ret);

    ret = concat("Hello", 1.2);
    std::println("Result: {}", ret);

    return 0;
}