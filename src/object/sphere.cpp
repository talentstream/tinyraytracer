#include "sphere.hpp"

bool Sphere::intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const
{
    // 计算光线是否与球相交, 且算出发现交点的参数t
    Vec3 oc = r.origin() - center_;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius_ * radius_;

    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;
    auto delta = sqrt(discriminant);

    auto solution = (-half_b - delta) / a;

    if (solution < t_min || t_max < solution)
    {
        solution = (-half_b + delta) / a;
        if (solution < t_min || t_max < solution)
            return false;
    }

    intersection.update(solution, r.at(solution), (r.at(solution) - center_) / radius_, material_);
    // hit_point.t_ = solution;
    // hit_point.pos_ = r.at(hit_point.t_);
    // Vec3 outward_normal = unit_vector(hit_point.pos_ - center_);
    // hit_point.set_face_normal(r, outward_normal);

    return true;
}