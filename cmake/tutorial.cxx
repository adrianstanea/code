#include "TutorialConfig.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>
#ifdef USE_MY_MATH
#include "MathFunctions.h"
#endif // USE_MY_MATH


using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "Version: " <<
            Tutorial_VERSION_MAJOR << "." <<
            Tutorial_VERSION_MINOR << "." <<
            Tutorial_VERSION_PATCH << endl;
        cout << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }

    const double input_value = std::stod(argv[1]);
#ifdef USE_MY_MATH
    cout << "Using custom my_sqrt function" << std::endl;
    const double output_value = my_sqrt(input_value);
#else
    cout << "Using standard sqrt function" << std::endl;
    const double output_value = sqrt(input_value);
#endif // DEBUG

    cout << "The square root of " << input_value << " is " << output_value << std::endl;

    return 0;
}
