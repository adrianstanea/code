#pragma once

#include <string>
#include <string_view>

class SpreadSheetCell
{
public:
    SpreadSheetCell() = default;
    SpreadSheetCell(double initial_value);
    explicit SpreadSheetCell(std::string_view initial_value);
    SpreadSheetCell(const SpreadSheetCell& src);
    ~SpreadSheetCell();

    SpreadSheetCell& operator=(const SpreadSheetCell& rhs);

    void setValue(double value);
    double getValue() const;

    void setString(std::string_view value);
    std::string getString() const;

private:
    std::string doubleToString(double value) const;
    double stringToDouble(std::string_view value) const;

    double m_value { 0.0 };
};