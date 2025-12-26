#pragma once
#include <cstddef>
#include <cstdint>
#include <format>
#include <print>
#include <string>
#include <utility>

#include "Person.hpp"

namespace HR {

class Employee : public Person {
   public:
    virtual ~Employee() = default;
    Employee() : Person(), m_ID(s_counter++) {}
    Employee(std::string first_name, std::string last_name)
        : Person(std::move(first_name), std::move(last_name)),
          m_ID(s_counter++) {}
    Employee(std::string first_name, std::string last_name, int64_t id)
        : Employee(std::move(first_name), std::move(last_name)) {
        m_ID = id;
    }

    Employee(const Employee &) = default;
    Employee(Employee &&) = delete;
    Employee &operator=(const Employee &) = default;
    Employee &operator=(Employee &&) = delete;

    [[nodiscard]] int64_t get_id() const { return m_ID; }

    [[nodiscard]] std::string toString() const override {
        return std::format("Employee with ID={}, {}", m_ID, Person::toString());
    }

   private:
    int64_t m_ID{0};
    static inline int64_t s_counter = 0;
};

}  // namespace HR
