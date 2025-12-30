import person;
// the person module does not export the std module, even though it used it in
// it's impementation, hence we still need to import std in client code
// import std;
// using namespace std;

int main() {
    auto person{HR::Person("John", "Doe")};
    // println("{}, {}", person.get_first_name(), person.get_last_name());

    // The functionality imported from the person module is visible to this
    // executable. We can use the interfaces it provides even if we don't
    // explicitly import the same modules that person uses internally In this
    // case the return type is a std::string that can be deduced with auto
    const auto& last_name{person.get_last_name()};
    auto length{last_name.length()};

    return 0;
}
