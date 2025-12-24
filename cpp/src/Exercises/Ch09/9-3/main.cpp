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

    println("{} {} ({})", person.get_first_name(), person.get_last_name(),
            person.get_initials());

    Person person2{"Marc", "Gregoire", "Mg"};
    println("{} {} ({})", person2.get_first_name(), person2.get_last_name(),
            person2.get_initials());

    println("");
    Person persons[3];

    println("");
    Person copy{person};  // Copy constructor

    // Test assignment operator
    println("");
    Person otherPerson{"Jane", "Smith"};
    copy = otherPerson;  // Copy assignment operator

    // Test comparison operators
    println("");
    println("person={}, person2={}", person.get_first_name(),
            person2.get_first_name());
    if (person == person2) {
        println("person == person2");
    }
    if (person != person2) {
        println("person != person2");
    }
    if (person < person2) {
        println("person < person2");
    }
    if (person <= person2) {
        println("person <= person2");
    }
    if (person > person2) {
        println("person > person2");
    }
    if (person >= person2) {
        println("person >= person2");
    }
}
