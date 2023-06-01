#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

// System Headers

#include <iostream>
#include <cmath>
#include <memory>
#include <limits>

namespace Utility
{
    // Constants

    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;


    inline double degrees_to_radians(double degrees)
    {
        return degrees * pi / 180.0;
    }
}

#endif /* _UTILITY_HPP_ */