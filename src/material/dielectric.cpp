#include "dielectric.hpp"

double reflectance(double cosine, double ref_idx)
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;

    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double refraction_ratio = intersection.front_face() ? (1.0 / refraction_) : refraction_;

    Vec3 unit_direction = unit_vector(r_in.direction());

    double cos_theta = fmin(dot(-1 * unit_direction, intersection.normal()), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;

    Vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > double_random())
        direction = reflect(unit_direction, intersection.normal());
    else
        direction = refract(unit_direction, intersection.normal(), refraction_ratio);

    scattered = Ray(intersection.position(), direction);

    return true;
}
