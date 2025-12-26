#pragma once
#include "Employee.hpp"

namespace HR {
class Director : public Employee {
   public:
    // Explicitly inherit Employee's constructors
    using Employee::Employee;
};

}  // namespace HR