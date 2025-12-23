#include "Person.hpp"

#include <print>
#include <string>

Person::Person(std::string first_name, std::string last_name)
    : Person::Person(first_name, last_name,
             get_initials(first_name, last_name)) {
    std::println("{} called", __PRETTY_FUNCTION__);
    // Delegates to the other constructor.
    // First the 3-parameter constructor is called, then the body of this
    // constructor. Why: because first the initializer list is processed.
}

Person::Person(std::string first_name, std::string last_name,
               std::string initials)
    : m_first_name{std::move(first_name)},
      m_last_name{std::move(last_name)},
      m_initials{std::move(initials)} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

std::string Person::get_first_name() const { return m_first_name; }

std::string Person::get_last_name() const { return m_last_name; }

void Person::set_first_name(const std::string& first_name) {
    m_first_name = first_name;
}
void Person::set_last_name(const std::string& last_name) {
    m_last_name = last_name;
}

std::string Person::get_initials(const std::string& first_name,
                                 const std::string& last_name) {
    if (first_name.empty() || last_name.empty()) {
        return "";
    }

    auto initials = first_name.substr(0, 1) + "." + last_name.substr(0, 1);
    std::println("Initials: {}", initials);
    return initials;
}