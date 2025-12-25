#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "SpreadSheetCell.hpp"

class DoubleSpreadSheetCell : public SpreadSheetCell {
   public:
    DoubleSpreadSheetCell() = default;
    DoubleSpreadSheetCell(double value);
    virtual void set(double value);
    [[nodiscard]] virtual double getValue() const;

    void set(std::string_view value) override;
    [[nodiscard]] std::string getString() const override;

   protected:
    static std::string doubleToString(double value);
    static double stringToDouble(std::string_view value);

   private:
    std::optional<double> m_value;
};

DoubleSpreadSheetCell operator+(const DoubleSpreadSheetCell& lhs,
                                     const DoubleSpreadSheetCell& rhs);