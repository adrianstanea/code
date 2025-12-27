
#include <array>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <limits>
#include <optional>
#include <print>

using namespace std;

template <typename T>
std::optional<size_t> Find(const T& value, const T* array, std::size_t size) {
    std::println("Using General Template...");
    for (size_t i{0}; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return std::nullopt;
}

template <typename T, size_t N>
std::optional<std::size_t> Find(const T& value, const T (&array)[N]) {
    std::println("Using Array Template...");
    return Find(value, array, N);
}

template <std::floating_point T>
bool AreEqual(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) {
    return std::abs(a - b) <= epsilon;
}

// Constraint based template function specialization
// We can change the implementation for certain specialized types of the
// template function
template <std::floating_point T>
std::optional<size_t> Find(const T& value, const T* array, std::size_t size) {
    std::println("Using Floating Point Template Specialization...");
    for (size_t i{0}; i < size; i++) {
        if (AreEqual(array[i], value)) {
            return i;
        }
    }
    return std::nullopt;
}

int main(int argc, const char** argv) {
    // Do not declare C-style arrays, use std::array<>
    // insteadclang-tidycppcoreguidelines-avoid-c-arrays
    int myInt = 3;
    std::array intArray{1, 2, 3, 4, 5};

    auto index = Find(myInt, intArray.data(), intArray.size());

    if (index.has_value()) {
        std::cout << "Found value " << myInt << " at index: " << index.value()
                  << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    double myDouble = 3.14;
    std::array doubleArray{1.1, 2.2, 3.14, 4.4, 5.5};

    index = Find(myDouble, doubleArray.data(), doubleArray.size());

    if (index.has_value()) {
        std::cout << "Found value " << myDouble
                  << " at index: " << index.value() << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    int myOtherInt = 10;
    int stackIntArray[]{10, 20, 30, 40, 50};
    auto res{Find(myOtherInt, stackIntArray)};
    if (res.has_value()) {
        std::cout << "Found value " << myOtherInt
                  << " at index: " << res.value() << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}