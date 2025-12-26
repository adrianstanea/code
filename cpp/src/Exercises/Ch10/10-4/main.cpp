#include <memory>
#include <print>
#include <vector>

#include "Director.hpp"
#include "Employee.hpp"
#include "Manager.hpp"
#include "Person.hpp"

using namespace std;

void printPerson(const HR::Person& employee) {
    std::println("{}", employee.toString());
}

int main(int argc, const char** argv) {
    auto employees{std::vector<std::unique_ptr<HR::Employee>>()};

    employees.push_back(std::make_unique<HR::Employee>("John1", "Doe"));
    employees.push_back(std::make_unique<HR::Employee>("John2", "Doe"));
    employees.push_back(std::make_unique<HR::Employee>("John3", "Doe"));
    employees.push_back(std::make_unique<HR::Manager>("Mr", "Manager"));
    employees.push_back(std::make_unique<HR::Director>("Mr", "Director"));

    for (const auto& employee : employees) {
        println("{}", employee->toString());
    }

    auto employee{HR::Employee("Employee", "Test")};
    println("{}", employee.toString());
    auto manager{HR::Manager(employee)};
    println("{}", manager.toString());

    auto director{HR::Director(employee)};
    println("{}", director.toString());

    return 0;
}