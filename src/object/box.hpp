#ifndef _BOX_H
#define _BOX_H

#include "../core/object.hpp"
#include "../object/plane.hpp"

class Box : public Object
{
public:
    Point3 box_min_;
    Point3 box_max_;
    std::vector<Object *> planes;

public:
    Box() {}
    Box(Point3 box_min, Point3 box_max, const Material *material);
    ~Box() {}

    virtual bool Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const override;
    virtual bool BoundingBox(double t_min, double t_max, AABB &aabb) const override
    {
        aabb = AABB(box_min_, box_max_);
        return true;
    }
};

#endif /* _BOX_H */