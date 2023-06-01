#include "utility.hpp"

namespace Utility
{
    void write_color(std::ostream &out, Color pixel_color)
    {
        out << static_cast<int>(255.999 * pixel_color[0]) << ' '
            << static_cast<int>(255.999 * pixel_color[1]) << ' '
            << static_cast<int>(255.999 * pixel_color[2]) << '\n';
    }

    double hit_sphere(const Point3 &center, double radius, const Ray &r)
    {
        // 计算光线是否与球相交, 且算出发现交点的参数t
        Vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = half_b * half_b - a * c;
        return discriminant < 0 ? -1.0 : (-half_b - sqrt(discriminant)) / a;
    }

    Color ray_color(const Ray &r, const Object &scene)
    {
        // 计算球体的法向量
        HitRecord rec;
        if (scene.hit(r, 0, infinity, rec) > 0.0)
        {
            return 0.5 * (rec.normal + Color(1, 1, 1));
        }

        // 计算背景色
        Vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
}