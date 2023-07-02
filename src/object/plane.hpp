#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include "../core/object.hpp"
#include "../math/ray.hpp"

class XYPlane : public Object
{
private:
    double x0_, y0_, x1_, y1_, z_;
    const Material *material_;

public:
    XYPlane() {}
    XYPlane(double x0, double y0, double x1, double y1, double z, const Material *material)
        : x0_(x0), y0_(y0), x1_(x1), y1_(y1), z_(z), material_(material) {}
    ~XYPlane() {}

    virtual bool Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const override;
    virtual bool BoundingBox(double t_min, double t_max, AABB &aabb) const override
    {
        aabb = AABB(Point3(x0_, y0_, z_ - 0.0001), Point3(x1_, y1_, z_ + 0.0001));
        return true;
    }
};

class XZPlane : public Object
{
private:
    double x0_, z0_, x1_, z1_, y_;
    const Material *material_;

public:
    XZPlane() {}
    XZPlane(double x0, double z0, double x1, double z1, double y, const Material *material)
        : x0_(x0), z0_(z0), x1_(x1), z1_(z1), y_(y), material_(material) {}
    ~XZPlane() {}

    virtual bool Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const override;
    virtual bool BoundingBox(double t_min, double t_max, AABB &aabb) const override
    {
        aabb = AABB(Point3(x0_, y_ - 0.0001, z0_), Point3(x1_, y_ + 0.0001, z1_));
        return true;
    }
};

class YZPlane : public Object
{
private:
    double y0_, z0_, y1_, z1_, x_;
    const Material *material_;

public:
    YZPlane() {}
    YZPlane(double y0, double z0, double y1, double z1, double x, const Material *material)
        : y0_(y0), z0_(z0), y1_(y1), z1_(z1), x_(x), material_(material) {}
    ~YZPlane() {}

    virtual bool Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const override;
    virtual bool BoundingBox(double t_min, double t_max, AABB &aabb) const override
    {
        aabb = AABB(Point3(x_ - 0.0001, y0_, z0_), Point3(x_ + 0.0001, y1_, z1_));
        return true;
    }
};
#endif /* _PLANE_HPP_ */