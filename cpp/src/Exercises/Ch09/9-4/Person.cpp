#include "Person.hpp"

#include <algorithm>
#include <cctype>
#include <format>
#include <print>
#include <string>
#include <utility>

using namespace std;

class Person::Impl {
   public:
   public:
    explicit Impl() = default;
    explicit Impl(std::string first_name, std::string last_name);
    explicit Impl(std::string first_name, std::string last_name,
                  std::string initials);

    std::string get_first_name() const;
    void set_first_name(std::string first_name);

    std::string get_last_name() const;
    void set_last_name(std::string last_name);

    std::string get_initials() const;
    void set_initials(std::string initials);

   private:
    std::string m_first_name{""};
    std::string m_last_name{""};
    std::string m_initials{""};
};

Person::Impl::Impl(std::string first_name, std::string last_name)
    : m_first_name{std::move(first_name)}, m_last_name{std::move(last_name)} {
    m_initials = std::format("{}.{}", m_first_name.at(0), m_last_name.at(0));
    std::transform(m_initials.begin(), m_initials.end(), m_initials.begin(),
                   [](auto c) { return std::toupper(c); });
}

Person::Impl::Impl(std::string first_name, std::string last_name,
                   std::string initials)
    : m_first_name{std::move(first_name)},
      m_last_name{std::move(last_name)},
      m_initials{std::move(initials)} {}

std::string Person::Impl::get_first_name() const { return m_first_name; }

void Person::Impl::set_first_name(std::string first_name) {
    m_first_name = std::move(first_name);
}
std::string Person::Impl::get_last_name() const { return m_last_name; }
void Person::Impl::set_last_name(std::string last_name) {
    m_last_name = std::move(last_name);
}
std::string Person::Impl::get_initials() const { return m_initials; }
void Person::Impl::set_initials(std::string initials) {
    m_initials = std::move(initials);
}

// =============================================================================
// PImpl implementation
// =============================================================================

Person::Person() : m_impl{std::make_unique<Impl>()} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person::Person(std::string first_name, std::string last_name)
    : m_impl{
          std::make_unique<Impl>(std::move(first_name), std::move(last_name))} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person::Person(std::string first_name, std::string last_name,
               std::string initials)
    : m_impl{std::make_unique<Impl>(std::move(first_name), std::move(last_name),
                                    std::move(initials))} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person::Person(const Person& other)
    : m_impl{std::make_unique<Impl>(*other.m_impl)} {
    std::println("{} called", __PRETTY_FUNCTION__);
}

Person& Person::operator=(const Person& other) {
    std::println("{} called", __PRETTY_FUNCTION__);
    *m_impl = *other.m_impl;
    return *this;
}

Person::~Person() = default;
Person::Person(Person&& other) noexcept = default;
Person& Person::operator=(Person&& other) noexcept = default;

std::string Person::get_first_name() const { return m_impl->get_first_name(); }
void Person::set_first_name(std::string first_name) {
    m_impl->set_first_name(std::move(first_name));
}

std::string Person::get_last_name() const { return m_impl->get_last_name(); }
void Person::set_last_name(std::string last_name) {
    m_impl->set_last_name(std::move(last_name));
}
std::string Person::get_initials() const { return m_impl->get_initials(); }
void Person::set_initials(std::string initials) {
    m_impl->set_initials(std::move(initials));
}