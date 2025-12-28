#include <concepts>
#include <cstddef>
#include <exception>
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "FileError.hpp"

template <typename T1, typename T2>
    requires std::floating_point<T1> ||
             (std::integral<T1> && std::floating_point<T2>) || std::integral<T2>
decltype(auto) safe_division(T1 dividend, T2 divisor) {
    if (divisor == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return dividend / divisor;
}

std::vector<int> readIntegersFromFile(const std::string& file_name) {
    std::ifstream input_stream;

    input_stream.open(file_name);
    if (input_stream.fail()) {
        // throw std::ios_base::failure(
        //     std::format("Failed to open file: {}", file_name));
        throw FileOpenError{file_name};
    }

    std::vector<int> values;
    std::size_t line_number{0};

    while (!input_stream.eof()) {
        // Read line by line to track line numbers
        ++line_number;
        std::string line;
        std::getline(input_stream, line);
        if (input_stream.fail() && !input_stream.eof()) {
            throw FileReadError{file_name, line_number};
        }

        // Now read integer from the line
        int value{0};
        auto line_stream = std::istringstream{line};
        while (line_stream >> value) {
            values.push_back(value);
        }

        if (!line_stream.eof()) {
            throw FileReadError{file_name, line_number};
        }
    }

    return values;
}

void g() { throw std::invalid_argument("Error from g()"); }

void f() {
    try {
        g();
    } catch (const std::exception& e) {
        std::println("Caught in f(): {}", e.what());
        throw;  // always rethrow like this to avoid slicing
        // this will cause slicing -> exception is rebuilt as std::exception
        // throw e;
    }
}

int main(int argc, const char** argv) {
    try {
        std::println("{}", safe_division(5, 2));
        std::println("{}", safe_division(5.2, 2.3));
        std::println("{}", safe_division(5.2, 0));
    } catch (std::invalid_argument& e) {
        std::println("Invalid argument: {}", e.what());
    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
    }

    // File reading example
    std::println("");
    static const std::string file_name =
        "/workspace/cpp/src/Examples/Ch14/Handling-Erros/values.txt";
    std::println("Reading integers from file: {}", file_name);
    try {
        auto values = readIntegersFromFile(file_name);
        for (const auto& value : values) {
            std::println("Read value: {}", value);
        }

        values = readIntegersFromFile("aslkjdsal_nkasd.txt");
    } catch (const FileError& e) {
        std::println(std::cerr, "Custom File error: {}", e.what());
    } catch (const std::ios_base::failure& e) {
        std::println(std::cerr, "File error: {}", e.what());
    } catch (const std::exception& e) {
        std::println(std::cerr, "Error: {}", e.what());
    } catch (...) {  // catch-all handler
        std::println(std::cerr, "An unknown error occurred.");
        throw;  // rethrow the exception
    }

    // Rethrowing example -> throw; vs throw e;
    try {
        f();
    } catch (const std::invalid_argument& e) {
        std::println("Caught invalid_argument in main(): {}", e.what());
    } catch (const std::exception& e) {
        std::println("Caught generic exception in main(): {}", e.what());
    }
    return 0;
}