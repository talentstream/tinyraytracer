#ifndef _LAMBERTIAN_HPP_
#define _LAMBERTIAN_HPP_

#include "../core/material.hpp"

class Lambertian : public Material
{
private:
    Color albedo_;

public:
    Lambertian(const Color &albedo) : albedo_(albedo) {}
    ~Lambertian() {}

    virtual bool Scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

#endif /* _LAMBERTIAN_HPP_ */