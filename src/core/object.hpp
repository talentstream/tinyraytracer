#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "../math/vec3.hpp"
#include "../math/ray.hpp"

struct HitPoint
{
    Point3 pos_;
    Vec3 normal_;
    double t_;
    bool front_face_;

    inline void set_face_normal(const Ray &r, const Vec3 &outward_normal)
    {
        front_face_ = dot(r.direction(), outward_normal) < 0;
        normal_ = front_face_ ? outward_normal : -1.0 * outward_normal;
    }
};

class Object
{
public:
    Object() = default;

    virtual bool hit(const Ray &r, double t_min, double t_max, HitPoint &hit_point) const = 0;

    virtual ~Object() {}
};

#endif /* _OBJECT_HPP_ */