#include <cstring>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

int main(int argc, const char** argv) {
    int i{7};
    cout << i << endl;

    char ch{'A'};
    cout << ch << endl;

    string str{"Hello, World!"};
    cout << str << endl;

    const auto* const test{"hello output stream"};
    cout.write(test, std::strlen(test));
    cout.flush();

    cout.put('A');
    cout.put('\n');

    bool myBool{true};
    cout << "This is the default bool format: " << myBool << endl;
    cout << boolalpha;
    cout << "This should be true: \t"  << myBool << endl;
    cout << noboolalpha;
    cout << "This should reset to 1: \t"  << myBool << endl;

    return 0;
}