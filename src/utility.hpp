#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

// System Headers

#include <iostream>
#include <cmath>
#include <memory>
#include <limits>
// Custom Headers

#include "./math/vec3.hpp"
#include "./math/ray.hpp"
#include "./object/sphere.hpp"
#include "object_list.hpp"

// Usings

using std::make_shared;
using std::shared_ptr;

namespace Utility
{
    // Constants

    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    // Utility Functions

    void write_color(std::ostream &out, Color pixel_color);

    double hit_sphere(const Point3 &center, double radius, const Ray &r);

    Color ray_color(const Ray &r, const Object &scene);

    inline double degrees_to_radians(double degrees)
    {
        return degrees * pi / 180.0;
    }
}

#endif /* _UTILITY_HPP_ */