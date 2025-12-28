#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <print>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Person.hpp"

class Database {
   public:
    void add_person(Person person);
    void save(const std::string& file_name) const;
    void load(const std::string& file_name);
    void clear();
    void outputAll(std::ostream& os = std::cout) const;

   private:
    std::vector<Person> m_persons;
};

void Database::add_person(Person person) {
    m_persons.push_back(std::move(person));
}

void Database::save(const std::string& file_name) const {
    std::ofstream ofs;

    ofs.open(file_name);

    if (ofs.is_open()) {
        auto path = std::filesystem::absolute(file_name);
        std::println("Saving database to file: {}", path.string());

        for (const auto& person : m_persons) {
            person.output(ofs);
        }
        ofs.close();
    }
}

void Database::load(const std::string& file_name) {
    std::ifstream ifs(file_name);
    if (!ifs.is_open()) {
        throw std::runtime_error("Unable to open file: " + file_name);
    }

    // Regex to match: (first_name=John, last_name=Doe, initials=JD)
    const auto& pattern{Person::get_output_regex()};

    std::string line;
    std::smatch matches;

    while (std::getline(ifs, line)) {
        auto path = std::filesystem::absolute(file_name);
        std::println("Loading database from file: {}", path.string());

        if (std::regex_search(line, matches, pattern) && matches.size() == 4) {
            auto person{Person{
                matches[std::to_underlying(Person::RegexGroup::FirstName)].str(),  // first_name
                matches[std::to_underlying(Person::RegexGroup::LastName)].str(),   // last_name
                matches[std::to_underlying(Person::RegexGroup::Initials)].str()    // initials
            }};
            m_persons.push_back(std::move(person));
        }
    }
    ifs.close();
}
void Database::clear() { m_persons.clear(); }
void Database::outputAll(std::ostream& os) const {
    for (const auto& person : m_persons) {
        person.output(os);
    }
}