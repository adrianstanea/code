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

double SpreadSheetCell::getValue() const
{
    return m_value;
}

void SpreadSheetCell::setString(std::string_view value)
{
    m_value = this->stringToDouble(value);
}

std::string SpreadSheetCell::getString() const
{
    return this->doubleToString(m_value);
}

std::string SpreadSheetCell::doubleToString(double value) const
{
    return to_string(value);
}

double SpreadSheetCell::stringToDouble(std::string_view value) const
{
    double number{0};
    from_chars(value.data(), value.data() + value.size(), number);
    return number;
}
