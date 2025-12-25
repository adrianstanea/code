#include <print>

class Base {
   public:
    Base() = default;
    Base(Base &&) = default;
    Base(const Base &) = default;
    Base &operator=(Base &&) = default;
    Base &operator=(const Base &) = default;
    ~Base() = default;

    virtual void someFunction() const { std::println("{}", __PRETTY_FUNCTION__); };

   protected:
    int m_protectedInt{0};

   private:
    int m_privateInt{0};
};

class Derived : public Base {
   public:
    void someFunction() const override {
        std::println("{}", __PRETTY_FUNCTION__);
    };
    void someOtherFunction() {
        std::println("{}", __PRETTY_FUNCTION__);
        m_protectedInt = 42;  // OK: accessible}
    };
};

class Foo final {}; // Preventing inheritance
// class Bar: public Foo {  // error: base 'Foo' is marked 'final'};

// # Overriding member functions: `change how a member function behaves in a derived class`
// Once a member function is declared as `virtual` in a base class, it remains virtual in all derived classes even if the `virtual` keyword is omitted in the derived class.

void test(const Base& base) {
    base.someFunction(); // Calls the overridden function in the derived class if applicable
}

int main(int argc, const char **argv) {
    auto base{Base()};
    base.someFunction();

    auto derived{Derived()};
    derived.someFunction();
    derived.someOtherFunction();

    // base.someOtherFunction(); // error: 'someOtherFunction' is not a member

    // Using base class pointer to derived class object -- demonstrates polymorphism
    Base& base_ref {derived};
    base_ref.someFunction();

    test(base);
    test(derived);

    return 0;
}