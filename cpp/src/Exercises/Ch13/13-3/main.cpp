#include <print>
#include <string>

#include "Database.hpp"
#include "Person.hpp"

using namespace std::string_literals;

static constexpr auto FILE_NAME = "database_output.txt"s;

int main(int argc, const char** argv) {
    Database db;
    db.add_person(Person{"John", "Doe"});
    db.add_person(Person{"Jane", "Smith"});
    db.add_person(Person{"Adrian Bogdan", "Stanea"});

    std::println("");
    std::println("Database contents before saving:");
    db.outputAll();

    std::println("");
    db.save(FILE_NAME);

    db.clear();
    std::println("State after clearing the database:");
    db.outputAll();

    db.load(FILE_NAME);
    db.outputAll();

    std::println("");
    return 0;
}