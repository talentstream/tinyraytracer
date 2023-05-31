#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "ray.hpp"
struct HitRecord
{
    Point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray &r, const Vec3 &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -1 * outward_normal;
    }
};

class Object
{
public:
    Object() = default;
    virtual ~Object() {}

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
};

#endif /* _OBJECT_HPP_ */