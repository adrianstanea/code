#pragma once
#include <memory>
#include <print>
#include <string>

class Person {
   public:
    explicit Person();
    explicit Person(std::string first_name, std::string last_name);
    explicit Person(std::string first_name, std::string last_name,
                    std::string initials);

    Person(const Person& other);                 // Copy constructor
    Person& operator=(const Person& other);      // Copy assignment operator
    Person(Person&& other) noexcept;             // Move constructor
    Person& operator=(Person&& other) noexcept;  // Move assignment operator
    ~Person();

    std::string get_first_name() const;
    void set_first_name(std::string first_name);

    std::string get_last_name() const;
    void set_last_name(std::string last_name);

    std::string get_initials() const;
    void set_initials(std::string initials);

   private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
