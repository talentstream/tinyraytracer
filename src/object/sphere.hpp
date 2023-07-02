#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include "../core/object.hpp"
#include "../math/ray.hpp"

class Sphere : public Object
{
private:
    Point3 center_;
    double radius_;
    const Material *material_;

public:
    Sphere() {}
    Sphere(Point3 center, double radius, const Material *material) : center_(center), radius_(radius), material_(material) {}
    ~Sphere() {}

    virtual bool Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const override;
    virtual bool BoundingBox(double t_min, double t_max, AABB &aabb) const override;
};

#endif /* _SPHERE_HPP_ */