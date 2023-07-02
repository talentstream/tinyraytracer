#ifndef _DIELECTRIC_HPP_
#define _DIELECTRIC_HPP_

#include "../core/material.hpp"

class Dielectric : public Material
{
private:
    double refraction_;

public:
    Dielectric(double refraction): refraction_(refraction) {}

    virtual bool Scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

#endif /* _DIELECTRIC_HPP_ */