#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include "../core/object.hpp"
#include "../math/ray.hpp"

class Sphere : public Object
{
private:
    Point3 center_;
    double radius_;

public:
    Sphere() {}
    Sphere(Point3 center, double radius) : center_(center), radius_(radius) {}
    ~Sphere() {}

    virtual bool intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const override;
};

#endif /* _SPHERE_HPP_ */