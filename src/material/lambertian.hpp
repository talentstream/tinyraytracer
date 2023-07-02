#ifndef _LAMBERTIAN_HPP_
#define _LAMBERTIAN_HPP_

#include "../core/material.hpp"
#include "../core/texture.hpp"
#include "../texture/solid_color_texture.hpp"

class Lambertian : public Material
{
private:
    Texture *albedo_texture_;

public:
    Lambertian(const Color &albedo)
    {
        albedo_texture_ = new SolidColorTexture(albedo);
    }
    Lambertian(Texture *albedo_texture) : albedo_texture_(albedo_texture) {}
    ~Lambertian() {}

    virtual bool Scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

#endif /* _LAMBERTIAN_HPP_ */