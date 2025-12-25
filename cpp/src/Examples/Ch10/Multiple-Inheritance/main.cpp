#include <print>
#include <utility>

class Animal {
   public:
    virtual ~Animal() = default;
    virtual void speak() = 0;
};

class Dog : public Animal {
   public:
    Dog() = default;
    Dog(const Dog &) = default;
    Dog(Dog &&) = delete;
    Dog &operator=(const Dog &) = default;
    Dog &operator=(Dog &&) = delete;
    virtual ~Dog() = default;

    virtual void bark() { std::println("Wof!"); }
    virtual void eat() { std::println("The Dog ate"); }

    void speak() override { bark(); }
};

class Bird : public Animal {
   public:
    Bird() = default;
    Bird(const Bird &) = default;
    Bird(Bird &&) = delete;
    Bird &operator=(const Bird &) = default;
    Bird &operator=(Bird &&) = delete;
    virtual ~Bird() = default;
    virtual void chirp() { std::println("Chirp!"); }
    virtual void eat() { std::println("The Bird ate"); }

    void speak() override { chirp(); }
};

class DogBird : public Dog, public Bird {
   public:
    using Bird::eat;  // explicitly state which version of eat should be used in
                      // the Class
};

void speak(Animal &animal) {
    if (typeid(animal) == typeid(Dog)) {
        auto dog = dynamic_cast<Dog &>(animal);
        dog.bark();
    } else if (typeid(animal) == typeid(Bird)) {
        auto dog = dynamic_cast<Bird &>(animal);
        dog.chirp();
    } else {
        std::println("Undefined ...");
    }
}

void do_speak(Animal &animal) { animal.speak(); }

int main(int argc, const char **argv) {
    auto animal{DogBird()};
    animal.bark();
    animal.chirp();

    // animal.eat(); // Compilation error because eat is amniguous - has 2
    // definitions dynamic_cast<Bird&>(animal).eat(); // Workaround - upcast to
    // a base class

    animal.eat();

    std::println("");

    auto dog{Dog()};
    auto bird{Bird()};
    speak(dog);
    speak(bird);

    std::println("");
    do_speak(dog);
    do_speak(bird);

    return 0;
}