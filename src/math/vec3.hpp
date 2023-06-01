#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <cmath>
#include <iostream>
#include <cassert>

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

#endif /* _VEC3_HPP_ */