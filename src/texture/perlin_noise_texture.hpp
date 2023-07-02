#ifndef _PERLIN_NOISE_TEXTURE_HPP_
#define _PERLIN_NOISE_TEXTURE_HPP_

#include "../core/texture.hpp"

class Perlin
{
private:
    static const int point_count_ = 256;
    Vec3 *rand_vec_;
    int *perm_x_;
    int *perm_y_;
    int *perm_z_;

public:
    Perlin();
    ~Perlin();
    double Noise(const Point3 &p) const;
    double Turbulence(const Point3 &p, int depth = 7) const;

private:
    static int *PerlinGeneratePerm();
    static void Permute(int *p, int n);
    static double TriLinearInterp(Vec3 c[2][2][2], double u, double v, double w);
};

class PerlinNoiseTexture : public Texture
{
public:
    Perlin perlin_;
    double scale_;

public:
    PerlinNoiseTexture() {}
    PerlinNoiseTexture(double scale) : scale_(scale) {}
    ~PerlinNoiseTexture() {}

    virtual Color Value(double u, double v, const Point3 &p) const override
    {
        return Color(1.0, 1.0, 1.0) * 0.5 *(1 + sin(scale_ * p.z() + 10 * perlin_.Turbulence(p)));
        //return Color(1.0, 1.0, 1.0) * 0.5 * (1.0 + perlin_.Noise(scale_ * p));
    }
};

#endif /* _PERLIN_NOISE_TEXTURE_HPP_ */