#pragma once

#include <iostream>

class vec3
{
public:
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double &operator[](int i);

    vec3 &operator+=(const vec3 &v);
    vec3 &operator*=(const double t);
    vec3 &operator/=(const double t);

    double length() const;
    double length_squared() const;

public:
    double e[3];
};

using point3 = vec3; // 3D point
using color = vec3;  // RGB color

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
    return vec3(t * v[0], t * v[1], t * v[2]);
}
inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}
inline vec3 operator/(const vec3 &v, double t)
{
    return (1 / t) * v;
}
inline double dot(const vec3 &u, const vec3 &v)
{
    return u[0] * v[0] +
           u[1] * v[1] +
           u[2] * v[2];
}
inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}