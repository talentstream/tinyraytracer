#ifndef _INTERSECTION_HPP_
#define _INTERSECTION_HPP_

#include "../math/vec3.hpp"
#include "../math/constant.hpp"

class Intersection
{
public:
    Intersection() : isect_time_(infinity) {}

    void update(double isect_time, const Point3 &position, const Vec3 &normal);

    void setIsectTime(double isect_time) { isect_time_ = isect_time; }
    void setPosition(const Point3 &position) { position_ = position; }
    void setNormal(const Vec3 &normal) { normal_ = normal; }

    bool miss() const { return isect_time_ == infinity; }

    double isect_time() const { return isect_time_; }
    Point3 position() const { return position_; }
    Vec3 normal() const { return normal_; }

private:
    double isect_time_;
    Point3 position_;
    Vec3 normal_;
};

#endif /* _INTERSECTION_HPP_ */