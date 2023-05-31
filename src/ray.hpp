#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "vec3.hpp"

// Ray Type
class Ray
{
private:
    Point3 origin_;
    Vec3 direction_;

public:
    Ray() {}
    Ray(const Point3 &origin, const Vec3 &direction) : origin_(origin), direction_(direction) {}
    ~Ray() {}

    Point3 origin() const { return origin_; }
    Vec3 direction() const { return direction_; }

    Point3 at(double t) const
    {
        return origin_ + t * direction_;
    }
};

#endif /* _RAY_HPP_ */