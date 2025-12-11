#include "SpreadSheetCell.hpp"
#include <charconv>
#include <print>

using namespace std;

// SpreadSheetCell::SpreadSheetCell()
//     : SpreadSheetCell{0.1}
// {
// }

SpreadSheetCell::SpreadSheetCell(double initial_value)
    : m_value{initial_value}
{
}

SpreadSheetCell::SpreadSheetCell(std::string_view initial_value)
    : m_value{this->stringToDouble(initial_value)}
{
}

SpreadSheetCell::SpreadSheetCell(const SpreadSheetCell &src)
    : m_value{src.m_value}
{
}

SpreadSheetCell::~SpreadSheetCell()
{
    println("SpreadSheetCell with value {} is being destroyed.", m_value);
}

SpreadSheetCell &SpreadSheetCell::operator=(const SpreadSheetCell &rhs)
{
    if(this == &rhs) {
        return *this;
    }
    m_value = rhs.m_value;
    return *this;
}

void SpreadSheetCell::setValue(double value)
{
    m_value = value;
}

auto SpreadSheetCell::getValue() const -> double
{
    return m_value;
}

void SpreadSheetCell::setString(std::string_view value)
{
    m_value = this->stringToDouble(value);
}

auto SpreadSheetCell::getString() const -> std::string
{
    return this->doubleToString(m_value);
}

auto SpreadSheetCell::doubleToString(double value) const -> std::string
{
    return to_string(value);
}

auto SpreadSheetCell::stringToDouble(std::string_view value) const -> double
{
    double number{0};
    from_chars(value.data(), value.data() + value.size(), number);
    return number;
}
