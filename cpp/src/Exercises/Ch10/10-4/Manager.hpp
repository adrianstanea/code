#pragma once
#include <format>
#include <string>

#include "Employee.hpp"

namespace HR {
class Manager : public Employee {
   public:
    // Explicitly inherit Employee's constructors
    using Employee::Employee;
    // explicit Manager(const Employee& e)
    //     : Employee::Employee(e.get_first_name(), e.get_last_name(),
    //                          e.get_id()) {}
    explicit Manager(const Employee& e) : Employee(e) {}

    [[nodiscard]] std::string toString() const override {
        return std::format("Manager which is {}", Employee::toString());
    }
};

}  // namespace HR