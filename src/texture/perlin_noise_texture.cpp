#include "perlin_noise_texture.hpp"

Perlin::Perlin()
{
    rand_vec_ = new Vec3[point_count_];
    for (int i = 0; i < point_count_; ++i)
    {
        rand_vec_[i] = unit_vector(vec3_random(-1, 1));
    }

    perm_x_ = PerlinGeneratePerm();
    perm_y_ = PerlinGeneratePerm();
    perm_z_ = PerlinGeneratePerm();
}

Perlin::~Perlin()
{
    delete[] rand_vec_;
    delete[] perm_x_;
    delete[] perm_y_;
    delete[] perm_z_;
}

int *Perlin::PerlinGeneratePerm()
{
    auto p = new int[point_count_];
    for (int i = 0; i < point_count_; ++i)
    {
        p[i] = i;
    }
    Permute(p, point_count_);
    return p;
}

void Perlin::Permute(int *p, int n)
{
    for (int i = n - 1; i > 0; --i)
    {
        int target = int_random(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}
double Perlin::TriLinearInterp(Vec3 c[2][2][2], double u, double v, double w)
{
    auto uu = u * u * (3 - 2 * u);
    auto vv = v * v * (3 - 2 * v);
    auto ww = w * w * (3 - 2 * w);

    auto result = 0.0;

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                Vec3 weight_vec(u - i, v - j, w - k);
                result += (i * u + (1 - i) * (1 - uu)) *
                          (j * v + (1 - j) * (1 - vv)) *
                          (k * w + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight_vec);
            }
        }
    }
    return result;
}
double Perlin::Noise(const Point3 &p) const
{
    auto u = p.x() - floor(p.x());
    auto v = p.y() - floor(p.y());
    auto w = p.z() - floor(p.z());

    auto i = static_cast<int>(floor(p.x()));
    auto j = static_cast<int>(floor(p.y()));
    auto k = static_cast<int>(floor(p.z()));

    Vec3 c[2][2][2];

    for (int di = 0; di < 2; ++di)
    {
        for (int dj = 0; dj < 2; ++dj)
        {
            for (int dk = 0; dk < 2; ++dk)
            {
                c[di][dj][dk] = rand_vec_[perm_x_[(i + di) & 255] ^
                                          perm_y_[(j + dj) & 255] ^
                                          perm_z_[(k + dk) & 255]];
            }
        }
    }
    return TriLinearInterp(c, u, v, w);
}

double Perlin::Turbulence(const Point3 &p, int depth) const
{
    auto result = 0.0;
    auto temp_p = p;
    auto weight = 1.0;

    for(int i = 0; i < depth; ++i)
    {
        result += weight * Noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(result);
}