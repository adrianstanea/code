#include "StringSpreadSheetCell.hpp"

StringSpreadSheetCell::StringSpreadSheetCell(const DoubleSpreadSheetCell& cell)
    : m_value(cell.getString()) {}

void StringSpreadSheetCell::set(std::string_view value) {
    m_value = std::string(value);
}
std::string StringSpreadSheetCell::getString() const {
    return m_value.value_or("");
}

StringSpreadSheetCell operator+(const StringSpreadSheetCell& lhs,
                                const StringSpreadSheetCell& rhs) {
    StringSpreadSheetCell result{};
    result.set(lhs.getString() + rhs.getString());
    return result;
}