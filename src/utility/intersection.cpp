#include "intersection.hpp"

#include "../core/material.hpp"

void Intersection::update(double isect_time, const Point3 &position, const Vec3 &normal, bool front_face, const Material *material)
{
    isect_time_ = isect_time;
    position_ = position;
    normal_ = normal;
    front_face_ = front_face;
    material_ = material;
}