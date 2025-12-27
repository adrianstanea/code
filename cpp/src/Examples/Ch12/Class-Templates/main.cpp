#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <numbers>
#include <print>
#include <vector>

#include "Grid.hpp"

template <typename T>
void fillGrid(Grid<T>& grid, const T& start_value) {
    T value = start_value;
    for (std::size_t y = 0; y < grid.getHeight(); ++y) {
        for (std::size_t x = 0; x < grid.getWidth(); ++x) {
            grid.at(x, y) = value;
            ++value;
        }
    }
}

template <typename T>
void printGrid(const Grid<T>& grid) {
    std::vector<T> rowValues;
    for (std::size_t y = 0; y < grid.getHeight(); ++y) {
        rowValues.reserve(grid.getWidth());

        for (std::size_t x = 0; x < grid.getWidth(); ++x) {
            const auto& cell = grid.at(x, y);
            if (cell.has_value()) {
                rowValues.push_back(cell.value());
            } else {
                rowValues.push_back(T{});
            }
        }

        for (const auto& value : rowValues) {
            std::print("{:4}", value);
        }
        std::println("");
        rowValues.clear();
    }
}

// Concepts
template <typename T>
concept Big = sizeof(T) > 4;

// Simple requirement example
template <typename T>
concept Incrementable = requires(T x) {
    x++;
    ++x;
};

void process(const Incrementable auto& t) {}

// Type requirement example
template <typename T>
concept C = requires { typename T::value_type; };

int main() {
    Grid<int> intGrid;
    Grid<double> doubleGrid{11, 11};

    std::println("{}", intGrid.at(0, 0).value_or(0));

    intGrid.at(0, 0) = 42;
    std::println("{}", intGrid.at(0, 0).value_or(0));

    intGrid.at(1, 1).has_value() ? std::println("Cell (1,1) has a value.")
                                 : std::println("Cell (1,1) is empty.");

    auto intGrid2{intGrid};  // Copy constructor
    intGrid.at(0, 0) = 43;

    std::println("{}", intGrid.at(0, 0).value_or(0));
    std::println("{}", intGrid2.at(0, 0).value_or(0));

    auto grid{Grid<std::unique_ptr<GamePiece>>{5, 5}};

    auto testGrid{Grid<int>{3, 3}};
    std::println("");
    fillGrid(testGrid, 8);
    printGrid(testGrid);

    // Concepts test
    static_assert(!Big<std::int16_t>);
    static_assert(!Big<std::int32_t>);
    static_assert(Big<std::int64_t>);

    process(42);
    // process(std::string{"Hello"}); 

    return 0;
}
