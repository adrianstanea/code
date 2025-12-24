#pragma once
#include <print>
#include <string>

// Task: adapt to pass strings in the most efficient way
// To add:
//    - Move constructor
//    - Move assignment operator
//
// Track calls with logs

class Person {
   public:
    explicit Person() = default;
    explicit Person(std::string first_name, std::string last_name);

    Person(const Person& other);                 // Copy constructor
    Person& operator=(const Person& other);      // Copy assignment operator
    Person(Person&& other) noexcept;             // Move constructor
    Person& operator=(Person&& other) noexcept;  // Move assignment operator
    ~Person();

    void swap(Person& other) noexcept;

    std::string get_first_name() const;
    std::string get_last_name() const;

    void set_last_name(const std::string& last_name);
    void set_first_name(const std::string& first_name);

   private:
    std::string m_first_name;
    std::string m_last_name;
};

void swap(Person& a, Person& b) noexcept;