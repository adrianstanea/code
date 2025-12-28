#pragma once
#include <ostream>
#include <print>
#include <regex>
#include <string>

class Person {
   public:
    enum class RegexGroup : int {
        FullMatch = 0,
        FirstName = 1,
        LastName = 2,
        Initials = 3
    };

   public:
    explicit Person() = default;
    explicit Person(std::string first_name, std::string last_name);
    explicit Person(std::string first_name, std::string last_name,
                    std::string initials);

    Person(const Person& other);                 // Copy constructor
    Person& operator=(const Person& other);      // Copy assignment operator
    Person(Person&& other) noexcept;             // Move constructor
    Person& operator=(Person&& other) noexcept;  // Move assignment operator
    ~Person();

    void swap(Person& other) noexcept;

    std::string get_first_name() const;
    std::string get_last_name() const;
    std::string get_initials() const;

    void set_last_name(std::string last_name);
    void set_first_name(std::string first_name);
    void set_initials(std::string initials);

    // The 3-way comparison operator adds support for: ==, !=, <, <=, >, >=
    [[nodiscard]] auto operator<=>(const Person& other) const = default;
    // Note: ordering is based on the order of member variables declared below

    void output(std::ostream& os) const;
    static std::regex get_output_regex();

   protected:
    [[nodiscard]] std::string compute_initials(std::string first_name,
                                               std::string last_name) const;

   private:
    std::string m_first_name{""};
    std::string m_last_name{""};
    std::string m_initials{""};
};

void swap(Person& a, Person& b) noexcept;