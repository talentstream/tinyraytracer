#include "../core/ray_tracer.hpp"
#include "../core/scene.hpp"
#include "../core/camera.hpp"
#include "../object/sphere.hpp"
#include "../material/lambertian.hpp"
#include "../material/metal.hpp"
#include "../material/dielectric.hpp"

int main()
{
    const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples = 10;
    const int depth = 50;

    // Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    Point3 origin(0, 0, 0);
    Vec3 horizontal(viewport_width, 0, 0);
    Vec3 vertical(0, viewport_height, 0);
    Vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    // Scene
    Point3 lookfrom(3, 3, 2);
    Point3 lookat(0, 0, -1);
    Vec3 up(0, 1, 0);
    double dist_to_focus = (lookfrom - lookat).length();
    double aperture = 2.0;
    Camera camera(lookfrom, lookat, up, 20, aspect_ratio, aperture, dist_to_focus);

    auto material_ground = new Lambertian(Color(0.8, 0.8, 0.0));
    auto material_center = new Lambertian(Color(0.1, 0.2, 0.5));
    auto material_left = new Dielectric(1.5);
    auto material_right = new Metal(Color(0.8, 0.6, 0.2), 0.0);

    Sphere sphere1(Point3(0, 0, -1), 0.5, material_center);
    Sphere sphere2(Point3(0, -100.5, -1), 100, material_ground);
    Sphere sphere3(Point3(-1, 0, -1), 0.5, material_left);
    Sphere sphere4(Point3(-1, 0, -1), -0.4, material_left);
    Sphere sphere5(Point3(1, 0, -1), 0.5, material_right);

    Scene scene(&camera, {&sphere1, &sphere2, &sphere3, &sphere4, &sphere5});

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth);

    ray_tracer.render();

    return 0;
}