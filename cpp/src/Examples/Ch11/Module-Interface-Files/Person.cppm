export module person;  // module declaration

// Only what is exported will be visible to clients of the `person` module
// Module interface: the collection of exported entities
//      Exported entities can be: classes, using directives, function
//      prototypes, etc...

import std;

export namespace HR {

class Person {
   public:
    Person(std::string first_name, std::string last_name);

    [[nodiscard]] const std::string& get_first_name() const;
    [[nodiscard]] const std::string& get_last_name() const;

   private:
    std::string m_first_name;
    std::string m_last_name;
};

}  // namespace HR