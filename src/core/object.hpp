#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "../math/vec3.hpp"
#include "../math/ray.hpp"
#include "../utility/intersection.hpp"


class Object
{
public:
    Object() = default;

    virtual bool intersect(const Ray &, double, double, Intersection &) const = 0;
    virtual ~Object() {}
};

#endif /* _OBJECT_HPP_ */