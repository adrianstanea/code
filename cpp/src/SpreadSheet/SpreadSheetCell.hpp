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

    auto operator=(const SpreadSheetCell& rhs) -> SpreadSheetCell&;

    void setValue(double value);
    [[nodiscard]] auto getValue() const -> double;

    void setString(std::string_view value);
    [[nodiscard]] auto getString() const -> std::string;

private:
    [[nodiscard]] auto doubleToString(double value) const -> std::string;
    [[nodiscard]] auto stringToDouble(std::string_view value) const -> double;

    double m_value { 0.0 };
};