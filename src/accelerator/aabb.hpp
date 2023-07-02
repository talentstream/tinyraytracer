#ifndef _AABB_HPP_
#define _AABB_HPP_

#include "../math/vec3.hpp"
#include "../math/ray.hpp"

class AABB
{

public:
    Point3 minimum_;
    Point3 maximum_;

public:
    AABB() {}
    AABB(const Point3 &minimum, const Point3 &maximum) : minimum_(minimum), maximum_(maximum) {}
    ~AABB() {}
    Point3 minimum() const { return minimum_; }
    Point3 maximum() const { return maximum_; }

    bool Hit(const Ray &ray, double t_min, double t_max) const;
};

inline AABB SurroundingBox(AABB box0, AABB box1)
{
    Point3 small(fmin(box0.minimum().x(), box1.minimum().x()),
                 fmin(box0.minimum().y(), box1.minimum().y()),
                 fmin(box0.minimum().z(), box1.minimum().z()));

    Point3 big(fmax(box0.maximum().x(), box1.maximum().x()),
               fmax(box0.maximum().y(), box1.maximum().y()),
               fmax(box0.maximum().z(), box1.maximum().z()));

    return AABB(small, big);
}

#endif /* _AABB_HPP_ */