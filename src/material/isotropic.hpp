#ifndef _ISOTROPIC_HPP_
#define _ISOTROPIC_HPP_

#include "../core/material.hpp"
#include "../texture/solid_color_texture.hpp"

class Isotropic : public Material
{
public:
    Texture *albedo_;
public:
    Isotropic() {}
    Isotropic(Color color) : albedo_(new SolidColorTexture(color)) {}
    Isotropic(Texture *albedo) : albedo_(albedo) {}
    ~Isotropic() {}

    virtual bool Scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const override
    {
        scattered = Ray(intersection.position(), random_in_unit_sphere(), r_in.time());
        attenuation = albedo_->Value(intersection.texture_u(), intersection.texture_v(), intersection.position());
        return true;
    }
};

#endif /* _ISOTROPIC_HPP_ */