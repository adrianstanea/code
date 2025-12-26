#pragma once
#include <print>
#include <string>

namespace HR {

class Person {
   public:
    explicit Person() = default;
    explicit Person(std::string first_name, std::string last_name);
    explicit Person(std::string first_name, std::string last_name,
                    std::string initials);

    Person(const Person& other);                 // Copy constructor
    Person& operator=(const Person& other);      // Copy assignment operator
    Person(Person&& other) noexcept;             // Move constructor
    Person& operator=(Person&& other) noexcept;  // Move assignment operator
    virtual ~Person() = default;

    void swap(Person& other) noexcept;

    [[nodiscard]] std::string get_first_name() const;
    [[nodiscard]] std::string get_last_name() const;
    [[nodiscard]] std::string get_initials() const;

    void set_last_name(std::string last_name);
    void set_first_name(std::string first_name);
    void set_initials(std::string initials);

   protected:
    [[nodiscard]] std::string compute_initials(std::string first_name,
                                               std::string last_name) const;

   private:
    std::string m_first_name{""};
    std::string m_last_name{""};
    std::string m_initials{""};
};

void swap(Person& a, Person& b) noexcept;

}  // namespace HR
