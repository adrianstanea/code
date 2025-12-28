#include <filesystem>
#include <iostream>
#include <ostream>
#include <print>
#include <string>

#include "Database.hpp"
#include "Person.hpp"

using namespace std::string_literals;

int main(int argc, const char** argv) {
    const auto directory_path{std::filesystem::temp_directory_path() /
                              "person_database_test"s};
    std::filesystem::create_directory(directory_path);
    if (!std::filesystem::exists(directory_path)) {
        std::println(std::cerr, "Failed to create temporary directory: {}",
                     directory_path.string());
        return 1;
    }
    std::println("Using temporary directory: {}", directory_path.string());

    Database db;
    db.add_person(Person{"John", "Doe"});
    db.add_person(Person{"Jane", "Smith"});
    db.add_person(Person{"Adrian Bogdan", "Stanea"});

    std::println("");
    std::println("Database contents before saving:");
    db.outputAll();

    std::println("");
    db.save(directory_path);

    db.clear();
    std::println("State after clearing the database:");
    db.outputAll();

    db.load(directory_path);
    db.outputAll();

    std::println("");

    // TEST no-discard
    std::println("TEST no-discard");
    auto person{Person{"John", "Doe"}};
    person.get_first_name();

    return 0;
}