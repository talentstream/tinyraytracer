#include"camera.hpp"

Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 up, double fov, double aspect_ratio)
{
    auto theta = degrees_to_radians(fov);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    auto w = unit_vector(lookfrom - lookat);
    auto u = unit_vector(cross(up, w));
    auto v = cross(w, u);

    origin_ = lookfrom;
    horizontal_ = viewport_width * u;
    vertical_ = viewport_height * v;
    lower_left_corner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - w;
}