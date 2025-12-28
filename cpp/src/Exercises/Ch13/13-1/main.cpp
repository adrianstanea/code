#include <fstream>
#include <iostream>
#include <print>
#include <sstream>  // Required for std::ostringstream

#include "Person.hpp"

static constexpr auto FILE_NAME = "person_output.txt";

int main(int argc, const char** argv) {
    auto person1 = Person("John", "Doe");

    std::println("Output to console using output method:");
    person1.output(std::cout);

    std::println("Output to a string stream: ");
    std::ostringstream oss;
    person1.output(oss);

    std::println("Output to a file: ");
    std::ofstream ofs;
    ofs.open(FILE_NAME);

    if (ofs.is_open()) {
        person1.output(ofs);
        std::println("Successfully wrote to person_output.txt");
        ofs.close();
    } else {
        std::println("Failed to open person_output.txt for writing.");
    }

    return 0;
}