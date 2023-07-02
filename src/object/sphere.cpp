#include "sphere.hpp"

bool Sphere::Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const
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

    Vec3 outward_normal = (r.at(solution) - center_) / radius_;
    bool front_face = dot(r.direction(), outward_normal) < 0;
    outward_normal = front_face ? outward_normal : -1 * outward_normal;

    // 求纹理uv
    auto theta = acos(-outward_normal.y());
    auto phi = atan2(-outward_normal.z(), outward_normal.x()) + M_PI;
    auto u = phi / (2 * M_PI);
    auto v = theta / M_PI;

    intersection.Update(solution, r.at(solution), outward_normal, front_face, material_, u, v);

    return true;
}

bool Sphere::BoundingBox(double t_min, double t_max, AABB &aabb) const
{
    aabb = AABB(center_ - Vec3(radius_, radius_, radius_),
                center_ + Vec3(radius_, radius_, radius_));
    return true;
}