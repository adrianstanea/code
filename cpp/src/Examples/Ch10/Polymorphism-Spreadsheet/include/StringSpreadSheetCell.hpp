#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "DoubleSpreadSHeetCell.hpp"
#include "SpreadSheetCell.hpp"

class StringSpreadSheetCell : public SpreadSheetCell {
   public:
   StringSpreadSheetCell() = default;
   StringSpreadSheetCell(const DoubleSpreadSheetCell& cell);
    void set(std::string_view value) override;
    [[nodiscard]] std::string getString() const override;

   private:
    std::optional<std::string> m_value;
};

StringSpreadSheetCell operator+(const StringSpreadSheetCell& lhs,
                                const StringSpreadSheetCell& rhs);