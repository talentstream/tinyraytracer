#include "metal.hpp"

bool Metal::scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    Vec3 reflected = reflect(unit_vector(r_in.direction()), intersection.normal());
    scattered = Ray(intersection.position(), reflected + fuzz_ * random_in_unit_sphere());
    attenuation = albedo_;
    return (dot(scattered.direction(), intersection.normal()) > 0);
}