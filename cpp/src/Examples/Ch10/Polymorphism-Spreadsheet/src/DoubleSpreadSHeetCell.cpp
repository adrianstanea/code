#include "DoubleSpreadSHeetCell.hpp"

#include <charconv>
#include <string>

DoubleSpreadSheetCell::DoubleSpreadSheetCell(double value) : m_value(value) {}

void DoubleSpreadSheetCell::set(double value) { m_value = value; }
double DoubleSpreadSheetCell::getValue() const { return m_value.value_or(0); }

void DoubleSpreadSheetCell::set(std::string_view value) {
    m_value = this->stringToDouble(value);
}

std::string DoubleSpreadSheetCell::getString() const {
    return (m_value.has_value() ? this->doubleToString(m_value.value()) : "");
}

std::string DoubleSpreadSheetCell::doubleToString(double value) {
    return std::to_string(value);
}
double DoubleSpreadSheetCell::stringToDouble(std::string_view value) {
    auto number{0.0};
    std::from_chars(value.data(), value.data() + value.size(), number);
    return number;
}

DoubleSpreadSheetCell operator+(const DoubleSpreadSheetCell& lhs,
                                const DoubleSpreadSheetCell& rhs) {
    DoubleSpreadSheetCell result;
    result.set(lhs.getValue() + rhs.getValue());
    return result;
}