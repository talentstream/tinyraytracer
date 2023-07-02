#ifndef _DIFFUSE_LIGHT_HPP_
#define _DIFFUSE_LIGHT_HPP_

#include "../core/material.hpp"
#include "../core/texture.hpp"
#include "../texture/solid_color_texture.hpp"

class DiffuseLight : public Material
{
private:
    Texture *emit_texture_;

public:
    DiffuseLight(const Color &emit)
    {
        emit_texture_ = new SolidColorTexture(emit);
    }
    DiffuseLight(Texture *emit_texture) : emit_texture_(emit_texture) {}
    ~DiffuseLight() {}

    virtual bool Scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const override
    {
        return false;
    }
    virtual Color Emitted(double u, double v, const Point3 &p) const override
    {
        return emit_texture_->Value(u, v, p);
    }
};

#endif /* _DIFFUSE_LIGHT_HPP_ */