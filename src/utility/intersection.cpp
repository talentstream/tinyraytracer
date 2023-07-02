#include "intersection.hpp"

#include "../core/material.hpp"

void Intersection::Update(double isect_time, const Point3 &position, const Vec3 &normal, bool front_face, const Material *material,double texture_u, double texture_v)
{
    isect_time_ = isect_time;
    position_ = position;
    normal_ = normal;
    front_face_ = front_face;
    material_ = material;
    texture_u_ = texture_u;
    texture_v_ = texture_v;
}