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

    println("{}", person.get_first_name());
    println("{}", Person("Jane", "Smith").get_first_name());

    auto&& first_name = Person("Jane", "Smith").get_first_name();
    const auto& test = first_name;

    println("{}", first_name);
    println("{}", test);
}