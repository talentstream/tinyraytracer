#include "plane.hpp"

bool Plane::Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const
{
    auto t = (z_ - r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max)
        return false;

    auto x = r.origin().x() + t * r.direction().x();
    auto y = r.origin().y() + t * r.direction().y();
    if (x < x0_ || x > x1_ || y < y0_ || y > y1_)
        return false;

    auto outward_normal = Vec3(0, 0, 1);
    bool front_face = dot(r.direction(), outward_normal) < 0;

    intersection.Update(t, r.at(t), outward_normal, front_face, material_, (x - x0_) / (x1_ - x0_), (y - y0_) / (y1_ - y0_));
    return true;
}