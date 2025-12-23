#include "Person.hpp"

#include <print>
#include <string>

Person::Person() : m_first_name{""}, m_last_name{""} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person::Person(std::string first_name, std::string last_name)
    : m_first_name{std::move(first_name)}, m_last_name{std::move(last_name)} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person& Person::operator=(const Person& other) {
    std::println("{} called", __PRETTY_FUNCTION__);
    if (this != &other) {
        std::println("Assigning values from one Person to another");
        m_first_name = other.m_first_name;
        m_last_name = other.m_last_name;
    } else {
        std::println("Self-assignment detected; no action taken.");
    }
    return *this;
}

Person::Person(const Person& other)
    : m_first_name(other.m_first_name), m_last_name(other.m_last_name) {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person::~Person() { std::println("{} called", __PRETTY_FUNCTION__); }

std::string Person::get_first_name() const { return m_first_name; }

std::string Person::get_last_name() const { return m_last_name; }

void Person::set_first_name(const std::string& first_name) {
    m_first_name = first_name;
}
void Person::set_last_name(const std::string& last_name) {
    m_last_name = last_name;
}