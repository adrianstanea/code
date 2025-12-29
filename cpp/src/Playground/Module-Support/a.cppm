export module MyModule;

import std;


int hidden() { return 42; }

export void printMessage() {

    std::println("The hidden value is {}\n", hidden());
}
