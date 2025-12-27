#pragma once

#include <algorithm>
#include <cstddef>
#include <format>  // For std::format
#include <memory>
#include <optional>
#include <stdexcept>  // For std::out_of_range
#include <utility>
#include <vector>

class GamePiece {
   public:
    virtual ~GamePiece() = default;
    virtual std::unique_ptr<GamePiece> clone() const = 0;
};

// Forward declarations needed for the friend declaration
template <typename T>
class Grid;

template <typename T>
Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs);

template <typename T>
class Grid {
   public:
    explicit Grid(std::size_t width = DefaultWidth,
                  std::size_t height = DefaultHeight);
    virtual ~Grid() = default;  // virtual defaulted destructor

    //    Explicitly default copy constructor and assignment operator
    Grid(const Grid& src) = default;
    Grid& operator=(const Grid& rhs) = default;

    // Explicitly default a move constructor and move assignment operator.
    Grid(Grid&& src) = default;
    Grid& operator=(Grid&& src) = default;

    std::optional<T>& at(std::size_t x, std::size_t y);
    const std::optional<T>& at(std::size_t x, std::size_t y) const;

    std::size_t getHeight() const { return m_height; }
    std::size_t getWidth() const { return m_width; }

    static constexpr std::size_t DefaultWidth{10};
    static constexpr std::size_t DefaultHeight{10};

    void swap(Grid& other) noexcept;

    friend Grid operator+ <T>(const Grid& lhs, const Grid& rhs);

   private:
    void verifyCoordinate(std::size_t x, std::size_t y) const;

    std::vector<std::optional<T>> m_cells;
    std::size_t m_width{0}, m_height{0};
};

template <typename T>
Grid<T>::Grid(size_t width, size_t height) : m_width{width}, m_height{height} {
    m_cells.resize(m_width * m_height);
}

template <typename T>
void Grid<T>::verifyCoordinate(size_t x, size_t y) const {
    if (x >= m_width) {
        throw std::out_of_range{
            std::format("x ({}) must be less than width ({}).", x, m_width)};
    }
    if (y >= m_height) {
        throw std::out_of_range{
            std::format("y ({}) must be less than height ({}).", y, m_height)};
    }
}

template <typename T>
void Grid<T>::swap(Grid& other) noexcept {
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

template <typename T>
void swap(Grid<T>& first, Grid<T>& second) noexcept {
    first.swap(second);
}

template <typename T>
const std::optional<T>& Grid<T>::at(size_t x, size_t y) const {
    verifyCoordinate(x, y);
    return m_cells[x + y * m_width];
}

template <typename T>
std::optional<T>& Grid<T>::at(size_t x, size_t y) {
    return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}

template <typename T>
Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs) {
    std::size_t minWidth{std::min(lhs.getWidth(), rhs.getWidth())};
    std::size_t minHeight{std::min(lhs.getHeight(), rhs.getHeight())};

    Grid<T> result{minWidth, minHeight};
    for (size_t i = 0; i < minWidth; i++) {
        for (size_t j = 0; j < minWidth; j++) {
            const auto& leftCell{lhs.at(i, j)};
            const auto& rightCell{rhs.at(i, j)};

            if (leftCell.has_value() && rightCell.has_value()) {
                result.at(i, j) = leftCell.value() + rightCell.value();
            }
        }
    }
    return result;
}
