#ifndef _SOLID_COLOR_HPP_
#define _SOLID_COLOR_HPP_

#include "../core/texture.hpp"

class SolidColorTexture : public Texture
{
private:
    Color color_;
public:
    SolidColorTexture() {}
    SolidColorTexture(Color color) : color_(color) {}
    ~SolidColorTexture() {}

    virtual Vec3 Value(double u, double v, const Point3 &p) const override
    {
        return color_;
    }
};

#endif /* _SOLID_COLOR_HPP_ */