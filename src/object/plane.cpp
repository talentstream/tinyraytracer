#include "plane.hpp"

bool XYPlane::Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const
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

bool XZPlane::Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const 
{
    auto t = (y_ - r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max)
        return false;

    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();
    if (x < x0_ || x > x1_ || z < z0_ || z > z1_)
        return false;

    auto outward_normal = Vec3(0, 1, 0);
    bool front_face = dot(r.direction(), outward_normal) < 0;

    intersection.Update(t, r.at(t), outward_normal, front_face, material_, (x - x0_) / (x1_ - x0_), (z - z0_) / (z1_ - z0_));
    return true;
}

bool YZPlane::Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const 
{
    auto t = (x_ - r.origin().x()) / r.direction().x();
    if (t < t_min || t > t_max)
        return false;

    auto y = r.origin().y() + t * r.direction().y();
    auto z = r.origin().z() + t * r.direction().z();
    if (y < y0_ || y > y1_ || z < z0_ || z > z1_)
        return false;

    auto outward_normal = Vec3(1, 0, 0);
    bool front_face = dot(r.direction(), outward_normal) < 0;

    intersection.Update(t, r.at(t), outward_normal, front_face, material_, (y - y0_) / (y1_ - y0_), (z - z0_) / (z1_ - z0_));
    return true;
}