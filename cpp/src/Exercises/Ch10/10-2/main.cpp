#include <memory>
#include <print>

#include "Director.hpp"
#include "Employee.hpp"
#include "Manager.hpp"
#include "Person.hpp"

using namespace std;

void printPerson(const HR::Person& employee) {
    std::println("{}", employee.toString());
}

int main(int argc, const char** argv) {
    auto employee1{HR::Employee("John1", "Doe")};
    auto employee2{HR::Employee("John2", "Doe")};
    auto employee3{HR::Employee("John3", "Doe")};

    printPerson(employee1);
    printPerson(employee2);
    printPerson(employee3);

    std::unique_ptr<HR::Employee> manager1{
        std::make_unique<HR::Manager>("Mr", "Manager")};
    printPerson(*manager1.get());

    std::unique_ptr<HR::Employee> director{
        make_unique<HR::Director>("Mr", "Director")};
    printPerson(*director.get());
    return 0;
}