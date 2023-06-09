#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include "../math/ray.hpp"
#include "../math/vec3.hpp"
#include "../utility/intersection.hpp"

class Material
{

public:
    Material() {}
    virtual ~Material() {}
    virtual bool Scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const = 0;
    virtual Color Emitted(double u, double v, const Point3 &p) const
    {
        return Color(0, 0, 0);
    }
};
#endif /* _MATERIAL_HPP_ */