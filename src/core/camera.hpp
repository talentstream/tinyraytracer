#ifndef _CMAERA_HPP_
#define _CMAERA_HPP_
#include "../math/vec3.hpp"
#include "../math/ray.hpp"

class Camera
{
private:
    Point3 origin_;
    Vec3 lower_left_corner_;
    Vec3 horizontal_;
    Vec3 vertical_;

public:
    Camera(Point3 lookfrom, Point3 lookat, Vec3 up, double fov, double aspect_ratio);

    Ray get_ray(double u, double v) const
    {
        return Ray(origin_, lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_);
    }
};

#endif /* _CMAERA_HPP_ */