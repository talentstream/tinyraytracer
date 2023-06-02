#ifndef _INTERSECTION_HPP_
#define _INTERSECTION_HPP_

#include "../math/vec3.hpp"
#include "../math/constant.hpp"

class Material;

class Intersection
{
public:
    Intersection() : isect_time_(infinity) {}

    void update(double isect_time, const Point3 &position, const Vec3 &normal, bool front_face, const Material *material);

    void setIsectTime(double isect_time) { isect_time_ = isect_time; }
    void setPosition(const Point3 &position) { position_ = position; }
    void setNormal(const Vec3 &normal) { normal_ = normal; }

    bool miss() const { return isect_time_ == infinity; }

    double isect_time() const { return isect_time_; }
    Point3 position() const { return position_; }
    Vec3 normal() const { return normal_; }
    bool front_face() const { return front_face_; }
    const Material *material() const { return material_; }

private:
    double isect_time_;
    Point3 position_;
    Vec3 normal_;
    bool front_face_;
    const Material *material_;
};

#endif /* _INTERSECTION_HPP_ */