#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <cmath>
#include <iostream>
#include <cassert>
#include <random>
// Vec3 Type

class Vec3
{
private:
    double e_[3];

public:
    Vec3() : e_{0, 0, 0} {}
    Vec3(double e0, double e1, double e2) : e_{e0, e1, e2} {}
    ~Vec3() {}

    double operator[](const int i) const
    {
        assert(i >= 0 && i < 3);
        return e_[i];
    }

    double &operator[](const int i)
    {
        assert(i >= 0 && i < 3);
        return e_[i];
    }

    Vec3 &operator+=(const Vec3 &v)
    {
        e_[0] += v[0];
        e_[1] += v[1];
        e_[2] += v[2];

        return *this;
    }

    Vec3 &operator-=(const Vec3 &v)
    {
        e_[0] -= v[0];
        e_[1] -= v[1];
        e_[2] -= v[2];

        return *this;
    }

    Vec3 &operator*=(const double t)
    {
        e_[0] *= t;
        e_[1] *= t;
        e_[2] *= t;

        return *this;
    }

    Vec3 &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    inline double x() const { return e_[0]; }
    inline double y() const { return e_[1]; }
    inline double z() const { return e_[2]; }

    inline double length() const
    {
        return std::sqrt(length_squared());
    }

    inline double length_squared() const
    {
        return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
    }
};

// Vec3 Usings

using Point3 = Vec3;
using Color = Vec3;

// Vec3 Utility Functions

inline std::ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(const double t, const Vec3 &v)
{
    return Vec3(t * v[0], t * v[1], t * v[2]);
}

inline Vec3 operator*(const Vec3 &v, const double t)
{
    return t * v;
}

inline Vec3 operator/(const Vec3 &v, const double t)
{
    return (1 / t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v)
{
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline Vec3 unit_vector(Vec3 v)
{
    return v / v.length();
}

inline double double_random()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline Vec3 vec3_random()
{
    return Vec3(double_random(), double_random(), double_random());
}

inline double double_random(double min, double max)
{
    return min + (max - min) * double_random();
}

inline int int_random(int min, int max)
{
    return static_cast<int>(double_random(min, max + 1));
}

inline Vec3 vec3_random(double min, double max)
{
    return Vec3(double_random(min, max), double_random(min, max), double_random(min, max));
}

inline double degrees_to_radians(double degrees)
{
    return degrees * M_PI / 180.0;
}

inline Vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto p = Vec3(double_random(-1, 1), double_random(-1, 1), double_random(-1, 1));
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

inline Vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = Vec3(double_random(-1, 1), double_random(-1, 1), 0);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

inline Vec3 random_in_vector()
{
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_in_hemisphere(const Vec3 &normal)
{
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else
        return -1 * in_unit_sphere;
}

inline bool near_zero(Vec3 v)
{
    const double s = 1e-8;
    return (std::fabs(v[0]) < s) && (std::fabs(v[1]) < s) && (std::fabs(v[2]) < s);
}

inline Vec3 reflect(const Vec3 &v, const Vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3 &R, const Vec3 &n, double etai_over_etat)
{
    auto cos_theta = dot(-1 * R, n);
    Vec3 r_out_parallel = etai_over_etat * (R + cos_theta * n);
    Vec3 r_out_perp = -std::sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}

#endif /* _VEC3_HPP_ */