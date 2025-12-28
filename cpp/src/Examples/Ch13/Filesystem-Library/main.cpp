#include <filesystem>
#include <print>


int main(int argc, const char** argv) {
    auto currentPath = std::filesystem::current_path();

    std::println("Current path is: {}", currentPath.string());

    for(const auto& entry : currentPath) {
        std::println("  {}", entry.string());
    }

    return 0;
}