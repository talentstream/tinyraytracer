#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include "../core/object.hpp"
#include "../math/ray.hpp"

class Plane : public Object
{
private:
    double x0_, y0_, x1_, y1_, z_;
    const Material *material_;

public:
    Plane() {}
    Plane(double x0, double y0, double x1, double y1, double z, const Material *material) : x0_(x0), y0_(y0), x1_(x1), y1_(y1), z_(z), material_(material) {}
    ~Plane() {}

    virtual bool Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const override;
    virtual bool BoundingBox(double t_min, double t_max, AABB &aabb) const override
    {
        aabb = AABB(Point3(x0_, y0_, z_ - 0.0001), Point3(x1_, y1_, z_ + 0.0001));
        return true;
    }
};

#endif /* _PLANE_HPP_ */