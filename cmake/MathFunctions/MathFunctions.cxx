#include "MathFunctions.h"
#include <cmath>

#ifdef USE_MY_MATh
#include "mysqrt.h"
#endif // USE_MY_MATh

namespace math_functions
{
    double sqrt(double x)
    {
#ifdef USE_MY_MATH
        return detail::my_sqrt(x);
#else
        return std::sqrt(x);
#endif
    }
}