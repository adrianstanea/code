#include <cstddef>
#include <print>

using namespace std;

class Base {
   public:
    Base() = default;
    virtual ~Base() = default;
};

class Derived : public Base {
   public:
    Derived() {
        m_string = new char[buffer_size];
        println("m_string allocated in Derived");
    }
    ~Derived() override {
        delete[] m_string;
        println("m_string deallocated in Derived");
    };

    static constexpr size_t buffer_size = 30;

   private:
    char* m_string;
};

int main(int argc, const char** argv) {
    Base* ptr{new Derived()};
    delete ptr;
    return 0;
}