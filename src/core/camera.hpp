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
    Vec3 u_, v_, w_;
    double lens_radius_;

public:
    Camera(Point3 lookfrom, Point3 lookat, Vec3 up, double fov, double aspect_ratio, double aperture, double focus_dist);

    Ray get_ray(double s, double t) const
    {
        Vec3 rd = lens_radius_ * random_in_unit_disk();
        Vec3 offset = u_ * rd.x() + v_ * rd.y();

        return Ray(origin_ + offset, lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_ - offset);
    }
};

#endif /* _CMAERA_HPP_ */