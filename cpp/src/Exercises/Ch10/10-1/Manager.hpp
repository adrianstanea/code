#pragma once
#include "Person.hpp"

namespace HR {
class Manager : public Employee {
   public:
    // Explicitly inherit Employee's constructors
    using Employee::Employee;
};

}  // namespace HR