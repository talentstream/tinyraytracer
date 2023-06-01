#include "intersection.hpp"

void Intersection::update(double isect_time, const Point3 &position, const Vec3 &normal)
{
    isect_time_ = isect_time;
    position_ = position;
    normal_ = normal;
}