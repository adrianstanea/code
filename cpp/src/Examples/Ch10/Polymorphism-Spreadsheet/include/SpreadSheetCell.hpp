#pragma once

#include <string_view>
class SpreadSheetCell {
   public:
    SpreadSheetCell() = default;
    SpreadSheetCell(SpreadSheetCell &&) = default;
    SpreadSheetCell(const SpreadSheetCell &) = default;
    SpreadSheetCell &operator=(SpreadSheetCell &&) = default;
    SpreadSheetCell &operator=(const SpreadSheetCell &) = default;
    virtual ~SpreadSheetCell() = default;

    // Declare pure virtual functions -> this makes the class abstract
    // No objects of this type can be created, the implmentation must come from a derived class
    virtual void set(std::string_view value) = 0;
    [[nodiscard]] virtual std::string getString() const = 0;

   private:
};
