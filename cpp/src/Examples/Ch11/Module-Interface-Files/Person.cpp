module person;  // module declaration

// This is the implementation of the person module (denotede by the module
// person above)

using namespace HR;

Person::Person(std::string first_name, std::string last_name)
    : m_first_name(std::move(first_name)), m_last_name(std::move(last_name)) {};

[[nodiscard]] const std::string& Person::get_first_name() const {
    return m_first_name;
    ;
}

[[nodiscard]] const std::string& Person::get_last_name() const {
    return m_last_name;
}