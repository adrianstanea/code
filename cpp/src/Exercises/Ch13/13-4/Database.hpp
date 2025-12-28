#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
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
    void save(const std::filesystem::path& directory) const;
    void load(const std::filesystem::path& directory);
    void clear();
    void outputAll(std::ostream& os = std::cout) const;

   private:
    std::vector<Person> m_persons;
};

void Database::add_person(Person person) {
    m_persons.push_back(std::move(person));
}

void Database::save(const std::filesystem::path& directory) const {
    std::ofstream ofs;

    auto whitespace_to_underscore = [](std::string& str) {
        std::replace_if(
            str.begin(), str.end(), [](char c) { return c == ' '; }, '_');
        return str;
    };

    auto get_formatted_file_name =
        [whitespace_to_underscore](const Person& person) {
            auto first_name = person.get_first_name();
            first_name = whitespace_to_underscore(first_name);

            auto last_name = person.get_last_name();
            last_name = whitespace_to_underscore(last_name);

            return std::format("{}_{}.person", first_name, last_name);
        };

    for (const auto& person : m_persons) {
        auto file_name = get_formatted_file_name(person);
        auto file_path = directory / file_name;

        ofs.open(file_path);
        if (!ofs.is_open()) {
            throw std::runtime_error("Unable to open file: " +
                                     file_path.string());
        }

        person.output(ofs);
        ofs.flush();
        ofs.close();
    }
}

void Database::load(const std::filesystem::path& directory) {
    auto load_person_from_file =
        [this](
            const std::filesystem::path& file_path) -> std::optional<Person> {
        std::ifstream ifs;

        ifs.open(file_path);
        if (!ifs.is_open()) {
            throw std::runtime_error("Unable to open file: " +
                                     file_path.string());
        }

        auto pattern = Person::get_output_regex();
        std::string line;
        std::smatch matches;

        // Read first line
        if (std::getline(ifs, line)) {
            if (std::regex_search(line, matches, pattern) &&
                matches.size() == 4) {
                auto person{Person{
                    matches[std::to_underlying(Person::RegexGroup::FirstName)]
                        .str(),  // first_name
                    matches[std::to_underlying(Person::RegexGroup::LastName)]
                        .str(),  // last_name
                    matches[std::to_underlying(Person::RegexGroup::Initials)]
                        .str()  // initials
                }};
                return std::make_optional(std::move(person));
            }
        }
        return std::nullopt;
    };

    auto directory_entries = std::filesystem::directory_iterator(directory);
    for (const auto& entry : directory_entries) {
        if (entry.path().extension() == ".person") {
            auto&& person = load_person_from_file(entry.path());
            if (person.has_value()) {
                m_persons.push_back(std::move(person.value()));
            }
        }
    }
}
void Database::clear() { m_persons.clear(); }
void Database::outputAll(std::ostream& os) const {
    for (const auto& person : m_persons) {
        person.output(os);
    }
}