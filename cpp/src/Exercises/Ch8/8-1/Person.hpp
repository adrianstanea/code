#pragma once
#include <print>
#include <string>

class Person {
   public:
    Person();
    Person(std::string first_name, std::string last_name);
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    std::string get_first_name() const;
    std::string get_last_name() const;

    void set_first_name(const std::string& first_name);
    void set_last_name(const std::string& last_name);

   private:
    std::string m_first_name;
    std::string m_last_name;
};
