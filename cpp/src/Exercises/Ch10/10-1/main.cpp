#include <memory>
#include <print>

#include "Director.hpp"
#include "Employee.hpp"
#include "Manager.hpp"

using namespace std;

void printEmployee(const HR::Employee& employee) {
    std::println("(first_name={}, last_name={}, initials={}, ID={})",
                 employee.get_first_name(), employee.get_last_name(),
                 employee.get_initials(), employee.get_id());
}

int main(int argc, const char** argv) {
    auto employee1{HR::Employee("John1", "Doe")};
    auto employee2{HR::Employee("John2", "Doe")};
    auto employee3{HR::Employee("John3", "Doe")};

    printEmployee(employee1);
    printEmployee(employee2);
    printEmployee(employee3);

    std::unique_ptr<HR::Employee> manager1{
        std::make_unique<HR::Manager>("Mr", "Manager")};
    printEmployee(*manager1.get());

    std::unique_ptr<HR::Employee> director{
        make_unique<HR::Director>("Mr", "Director")};
    printEmployee(*director.get());
    return 0;
}