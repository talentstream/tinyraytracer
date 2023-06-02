#include "intersection.hpp"

#include "../core/material.hpp"

void Intersection::update(double isect_time, const Point3 &position, const Vec3 &normal, const Material *material)
{
    isect_time_ = isect_time;
    position_ = position;
    normal_ = normal;
    material_ = material;

}