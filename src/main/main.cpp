#include "../core/ray_tracer.hpp"
#include "../core/scene.hpp"
#include "../core/camera.hpp"



int main()
{
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // // Scene
    // ObjectList sscene;
    // sscene.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    // sscene.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    Point3 origin(0, 0, 0);
    Vec3 horizontal(viewport_width, 0, 0);
    Vec3 vertical(0, viewport_height, 0);
    Vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    Camera camera(origin, lower_left_corner, horizontal, vertical);
    Scene scene(&camera, {nullptr});
    RayTracer ray_tracer(&scene, image_width, image_height);

    ray_tracer.render();

    return 0;
}