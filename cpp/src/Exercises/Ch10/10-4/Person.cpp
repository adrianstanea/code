#include "Person.hpp"

#include <algorithm>
#include <cctype>
#include <format>
#include <print>
#include <string>
#include <string_view>
#include <utility>

namespace HR {
using std::string;

Person::Person(std::string first_name, std::string last_name)
    : m_first_name{std::move(first_name)}, m_last_name{std::move(last_name)} {
    std::println("{} called", __PRETTY_FUNCTION__);
    m_initials = this->compute_initials(m_first_name, m_last_name);
}

Person::Person(std::string first_name, std::string last_name,
               std::string initials)
    : m_first_name{std::move(first_name)},
      m_last_name{std::move(last_name)},
      m_initials{std::move(initials)} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person::Person(const Person& other)
    : m_first_name(other.m_first_name),
      m_last_name(other.m_last_name),
      m_initials(other.m_initials) {
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

void Person::swap(Person& other) noexcept {
    std::swap(m_first_name, other.m_first_name);
    std::swap(m_last_name, other.m_last_name);
    std::swap(m_initials, other.m_initials);
}

string Person::get_first_name() const { return m_first_name; }

std::string Person::get_last_name() const { return m_last_name; }

std::string Person::get_initials() const { return m_initials; }

void Person::set_first_name(std::string first_name) {
    m_first_name = std::move(first_name);
}

void Person::set_last_name(std::string last_name) {
    m_last_name = std::move(last_name);
}

void Person::set_initials(std::string initials) {
    m_initials = std::move(initials);
}

std::string Person::toString() const {
    return std::format("first_name={}, last_name={}, (initials={}) is a person.",
                       get_first_name(), get_last_name(), get_initials());
}

void swap(Person& first, Person& second) noexcept { first.swap(second); }

std::string Person::compute_initials(std::string first_name,
                                     std::string last_name) const {
    if (first_name.empty() && last_name.empty()) {
        return "";
    }
    auto initials = std::format("{}.{}", first_name.at(0), last_name.at(0));
    std::transform(initials.begin(), initials.end(), initials.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return initials;
}

}  // namespace HR
