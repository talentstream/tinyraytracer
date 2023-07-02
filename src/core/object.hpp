#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "../math/vec3.hpp"
#include "../math/ray.hpp"
#include "../utility/intersection.hpp"
#include "../accelerator/aabb.hpp"

class Object
{
public:
    Object() = default;
    virtual ~Object() {}

    virtual bool Intersect(const Ray &, double, double, Intersection &) const = 0;
    virtual bool BoundingBox(double, double, AABB &) const = 0;    
};

#endif /* _OBJECT_HPP_ */