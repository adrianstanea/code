#include <concepts>
#include <cstddef>
#include <iterator>
#include <optional>
#include <print>

template <std::equality_comparable T>
std::optional<size_t> Find(const T& value, const T* arr, size_t size)

{
    for (size_t i{0}; i < size; ++i) {
        if (arr[i] == value) {
            return i;  // Found it; return the index.
        }
    }
    return {};  // Failed to find it; return empty optional.
}

// template <std::equality_comparable T,
//           size_t N>  //// Use the predefined std::equality_comparable
//           concept.
// std::optional<size_t> Find(const T& value, const T (&arr)[N]) {
//     return Find(value, arr, N);
// }

int main(int argc, const char** argv) {
    int myInt{3}, intArray[]{1, 2, 3, 4};
    const size_t sizeIntArray{std::size(intArray)};

    std::optional<size_t> res;
    res = Find(myInt, intArray, sizeIntArray);  // calls Find<int> by deduction.
    res = Find<int>(myInt, intArray,
                    sizeIntArray);  // calls Find<int> explicitly.
    // res = Find(myInt, intArray);
    if (res) {
        std::println("{}", *res);
    } else {
        std::println("Not found");
    }
    return 0;
}