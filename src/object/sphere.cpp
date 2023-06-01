#include "sphere.hpp"

bool Sphere::hit(const Ray &r, double t_min, double t_max) const
{
    // 计算光线是否与球相交, 且算出发现交点的参数t
    Vec3 oc = r.origin() - center_;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius_ * radius_;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;

    auto root = (-half_b - sqrt(discriminant)) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrt(discriminant)) / a;
        if (root < t_min || t_max < root)
            return false;
    }
    
    return true;
}