#ifndef _CHECKER_TEXTURE_HPP_
#define _CHECKER_TEXTURE_HPP_

#include "../core/texture.hpp"
#include "../texture/solid_color_texture.hpp"

class CheckerTexture : public Texture
{
public:
    Texture *odd_;
    Texture *even_;

public:
    CheckerTexture() {}
    CheckerTexture(Texture *odd, Texture *even) : odd_(odd), even_(even) {}
    CheckerTexture(Color odd, Color even) : odd_(new SolidColorTexture(odd)), even_(new SolidColorTexture(even)){}
    ~CheckerTexture() {}

    virtual Color Value(double u, double v, const Point3 &p) const override
    {
        auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        if (sines < 0)
        {
            return odd_->Value(u, v, p);
        }
        else
        {
            return even_->Value(u, v, p);
        }
    }
};

#endif /* _CHECKER_TEXTURE_HPP_ */