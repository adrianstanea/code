#include <string>

class Person {
   public:
    Person() = default;
    Person(std::string first_name, std::string last_name);
    Person(std::string first_name, std::string last_name, std::string initials);

    Person(const Person& other) = default;
    Person& operator=(const Person& other) = default;
    ~Person() = default;

    std::string get_first_name() const;
    std::string get_last_name() const;

    void set_first_name(const std::string& first_name);
    void set_last_name(const std::string& last_name);

   public:
    static std::string get_initials(const std::string& first_name,
                                    const std::string& last_name);

   private:
    std::string m_first_name;
    std::string m_last_name;
    std::string m_initials;
};
