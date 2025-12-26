#pragma once
#include "Employee.hpp"

namespace HR {
class Manager : public Employee {
   public:
    // Explicitly inherit Employee's constructors
    using Employee::Employee;

    [[nodiscard]] std::string toString() const override {
        return std::format("Manager is {}", Employee::toString());
    }
};

}  // namespace HR