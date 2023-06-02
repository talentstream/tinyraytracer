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
    virtual bool scatter(const Ray &r_in, const Intersection &intersection, Color &attenuation, Ray &scattered) const = 0;
};
#endif /* _MATERIAL_HPP_ */