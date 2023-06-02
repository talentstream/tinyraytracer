#include "lambertian.hpp"

bool Lambertian::scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    Vec3 scatter_direction = intersection.normal() + random_in_vector();
    if(near_zero(scatter_direction))
        scatter_direction = intersection.normal();
        
    scattered = Ray(intersection.position(), scatter_direction);
    attenuation = albedo_;
    return true;
}