#include <print>
#include <source_location>
#include <string_view>

#ifdef WITH_LOGS
void log_message(
    std::string_view message,
    const std::source_location& location = std::source_location::current()) {
    std::println("[{}:{} - {}] {}", location.file_name(), location.line(),
                 location.function_name(), message);
}

template <typename T>
constexpr void LOG_MESSAGE(T&& msg, const std::source_location& location =
                                        std::source_location::current()) {
    log_message(std::forward<T>(msg), location);
}
#else
template <typename T>
constexpr void LOG_MESSAGE(
    T&& /*unused*/,
    const std::source_location& /*unused*/ = std::source_location::current()) {}
#endif

void foo() { LOG_MESSAGE("This is a log message from foo()"); }

int main(int argc, const char** argv) {
    LOG_MESSAGE("This is a log message from main()");
    foo();
    return 0;
}