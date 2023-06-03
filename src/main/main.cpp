#include "../core/ray_tracer.hpp"
#include "../core/scene.hpp"
#include "../core/camera.hpp"
#include "../object/sphere.hpp"
#include "../material/lambertian.hpp"
#include "../material/metal.hpp"
#include "../material/dielectric.hpp"

#include <vector>

void easy_scene()
{
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples = 10;
    const int depth = 50;

    // Camera

    Point3 lookfrom(3, 3, 2);
    Point3 lookat(0, 0, -1);
    Vec3 up(0, 1, 0);
    double dist_to_focus = (lookfrom - lookat).length();
    double aperture = 2.0;

    Camera camera(lookfrom, lookat, up, 20, aspect_ratio, aperture, dist_to_focus);

    // Scene Setting
    auto material_ground = new Lambertian(Color(0.8, 0.8, 0.0));
    auto material_center = new Lambertian(Color(0.1, 0.2, 0.5));
    auto material_left = new Dielectric(1.5);
    auto material_right = new Metal(Color(0.8, 0.6, 0.2), 0.0);

    std::vector<Object *> objects;
    objects.push_back(new Sphere(Point3(0, -100.5, -1), 100, material_ground));
    objects.push_back(new Sphere(Point3(0, 0, -1), 0.5, material_center));
    objects.push_back(new Sphere(Point3(-1, 0, -1), 0.5, material_left));
    objects.push_back(new Sphere(Point3(-1, 0, -1), -0.4, material_left));
    objects.push_back(new Sphere(Point3(1, 0, -1), 0.5, material_right));

    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth);

    ray_tracer.render();
}
void random_scene()
{
    // Image
    const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples = 50;
    const int depth = 50;

    // Camera

    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 up(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    Camera camera(lookfrom, lookat, up, 20, aspect_ratio, aperture, dist_to_focus);

    // Scene Setting
    auto material_ground = new Lambertian(Color(0.5, 0.5, 0.5));
    std::vector<Object *> objects;
    objects.push_back(new Sphere(Point3(0, -1000, 0), 1000, material_ground));

    for (int a = -11; a < 11; ++a)
    {
        for (int b = -11; b < 11; ++b)
        {
            auto choose_mat = double_random();
            Point3 center(a + 0.9 * double_random(), 0.2, b + 0.9 * double_random());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {

                if(choose_mat < 0.8) // diffuse
                {
                    auto albedo = vec3_random() * vec3_random();

                    objects.push_back(new Sphere(center, 0.2, new Lambertian(albedo)));
                }
                else if(choose_mat < 0.95) // metal
                {
                    auto albedo = vec3_random(0.5, 1);
                    auto fuzz = double_random(0, 0.5);

                    objects.push_back(new Sphere(center, 0.2, new Metal(albedo, fuzz)));

                }
                else // glass 
                {

                    objects.push_back(new Sphere(center, 0.2, new Dielectric(1.5)));
                }
            }
        }
    }

    auto material1 = new Dielectric(1.5);
    objects.push_back(new Sphere(Point3(0, 1, 0), 1.0, material1));

    auto material2 = new Lambertian(Color(0.4, 0.2, 0.1));
    objects.push_back(new Sphere(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = new Metal(Color(0.7, 0.6, 0.5), 0.0);
    objects.push_back(new Sphere(Point3(4, 1, 0), 1.0, material3));

    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth);

    ray_tracer.render();

    return;
}

int main()
{
    // easy_scene();
    random_scene();
    return 0;
}