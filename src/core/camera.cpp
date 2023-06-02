#include "camera.hpp"

Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 up, double fov, double aspect_ratio, double aperture, double focus_dist)
{
    auto theta = degrees_to_radians(fov);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w_ = unit_vector(lookfrom - lookat);
    u_ = unit_vector(cross(up, w_));
    v_ = cross(w_, u_);

    origin_ = lookfrom;
    horizontal_ = focus_dist * viewport_width * u_;
    vertical_ = focus_dist * viewport_height * v_;
    lower_left_corner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - focus_dist * w_;

    lens_radius_ = aperture / 2;
}