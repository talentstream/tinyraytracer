#ifndef _METAL_HPP_
#define _METAL_HPP_

#include "../core/material.hpp"

class Metal : public Material
{
private:
    Color albedo_;
    double fuzz_;

public:
    Metal(const Color &albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1) {}
    ~Metal() {}

    virtual bool Scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const override;
};

#endif /* _METAL_HPP_ */