#include "Person.hpp"

#include <print>
#include <string>
#include <utility>

// Reasoning: arguments are passed by value, so we can utilize move semantics
// since those are temporary objects
Person::Person(std::string first_name, std::string last_name)
    : m_first_name{std::move(first_name)}, m_last_name{std::move(last_name)} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person::Person(const Person& other)
    : m_first_name(other.m_first_name), m_last_name(other.m_last_name) {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person& Person::operator=(const Person& other) {
    std::println("{} called", __PRETTY_FUNCTION__);
    auto temp{other};
    this->swap(temp);
    return *this;
}

Person::Person(Person&& other) noexcept {
    std::println("{} called", __PRETTY_FUNCTION__);
    this->swap(other);
}

Person& Person::operator=(Person&& other) noexcept {
    std::println("{} called", __PRETTY_FUNCTION__);
    auto moved{std::move(other)};
    this->swap(moved);
    return *this;
}

Person::~Person() { std::println("{} called", __PRETTY_FUNCTION__); }

void Person::swap(Person& other) noexcept {
    using std::swap;

    swap(m_first_name, other.m_first_name);
    swap(m_last_name, other.m_last_name);
}

std::string Person::get_first_name() const { return m_first_name; }

std::string Person::get_last_name() const { return m_last_name; }

void Person::set_first_name(const std::string& first_name) {
    m_first_name = first_name;
}
void Person::set_last_name(const std::string& last_name) {
    m_last_name = last_name;
}

void swap(Person& first, Person& second) noexcept
{
    first.swap(second);
}