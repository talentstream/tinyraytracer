#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "../math/vec3.hpp"

class Texture
{
public:
    Texture() {}
    virtual ~Texture() {}

    virtual Vec3 Value(double u, double v, const Point3 &p) const = 0;
};

#endif /* _TEXTURE_HPP_ */