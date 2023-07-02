#ifndef _BVH_HPP_
#define _BVH_HPP_

#include "../core/object.hpp"

#include <vector>

class BVHNode : public Object
{
public:
    Object *left_;
    Object *right_;
    AABB box_;

public:
    BVHNode() {}
    BVHNode(std::vector<Object *> &objects, int start, int end, double time0, double time1);
    ~BVHNode() {}

    virtual bool Intersect(const Ray &ray, double t_min, double t_max, Intersection &intersection) const override;
    virtual bool BoundingBox(double t_min, double t_max, AABB &aabb) const override;
};

#endif /* _BVH_HPP_ */