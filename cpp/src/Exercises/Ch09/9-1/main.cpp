#include <array>
#include <memory>
#include <ostream>
#include <print>
#include <string>
#include <utility>

#include "Person.hpp"

using namespace std;

int main(int argc, const char** argv) {
    Person person{"John", "Doe"};
    println("{} {}", person.get_first_name(), person.get_last_name());

    println("");

    auto persons = array<Person, 3>();

    println("");

    Person copy{person};  // Copy constructor

    println("");

    //     Test assignment operator
    Person otherPerson{"Jane", "Smith"};
    copy = otherPerson;  // Copy assignment operator

    println("");

    //     Test move constructor
    Person movedToPerson(std::move(copy));

    println("");

    // Test move assignment operator
    movedToPerson = std::move(person);

    return 0;
}