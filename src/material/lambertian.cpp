#include "lambertian.hpp"

bool Lambertian::Scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const
{
    Vec3 scatter_direction = intersection.normal() + random_in_vector();
    if(near_zero(scatter_direction))
        scatter_direction = intersection.normal();
        
    scattered = Ray(intersection.position(), scatter_direction);
    attenuation = albedo_texture_->Value(intersection.texture_u(), intersection.texture_v(), intersection.position());

    return true;
}