#include <array>
#include <memory>
#include <print>
#include <string>

#include "Person.hpp"

using namespace std;

int main(int argc, const char** argv) {
    auto p1{Person{"Jane", "Smith"}};
    println("First Name: {} \t Last Name: {}", p1.get_first_name(),
            p1.get_last_name());
    p1.set_first_name("John");
    p1.set_last_name("Doe");
    println("First Name: {} \t Last Name: {}", p1.get_first_name(),
            p1.get_last_name());
    auto p2{make_unique<Person>("John", "Doe")};
    println("First Name: {} \t Last Name: {}", p2->get_first_name(),
            p2->get_last_name());

    // Note: this requies default constructor to be defined
    println("Should call Default Constructor");
    auto persons_array = array<Person, 4>();
    println("Should call Copy Constructor");
    auto p3{p1};  // Copy constructor
    println("Should call Copy Assignment Operator");
    p3 = p1;  // Copy assignment operator
    p3 = p3;  // Copy assignment operator

    return 0;
}