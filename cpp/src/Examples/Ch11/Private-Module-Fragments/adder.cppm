module;  // global module fragment
// #define TEST_MACRO "Hello World"

export module adder;  // module interface definition

import std;

export constexpr auto TEST_MACRO = "Hello World";

export class Adder {
   public:
    Adder();
    virtual ~Adder();
    int add(int a, int b) const;

   private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

// =============================================================================
// private module fragment
// =============================================================================
module :private;

class Adder::Impl {
   public:
    virtual ~Impl() noexcept;
    int add(int a, int b);
};
int Adder::Impl::add(int a, int b) { return a + b; };
Adder::Impl::~Impl() {
    try {
        std::println("Destructor of Adder::Impl");
    } catch (...) {
        std::println("Destructor of Adder::Impl failed");
    }
};

Adder::Adder() : m_impl(std::make_unique<Impl>()) {}
Adder::~Adder() {}
int Adder::add(int a, int b) const { return m_impl->add(a, b); }