#include "../core/ray_tracer.hpp"
#include "../core/scene.hpp"
#include "../core/camera.hpp"
#include "../object/sphere.hpp"
#include "../material/lambertian.hpp"
#include "../material/metal.hpp"
#include "../material/dielectric.hpp"
#include "../Texture/checker_texture.hpp"

#include <vector>

// Image Settings
const double aspect_ratio = 16.0 / 9.0;
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);
const int samples = 10;
const int depth = 50;

void EasyScene();
void RandomScene();
void TwoCheckerSphereScene();

int main()
{
    int select_scene = 3;
    switch (select_scene)
    {
    case 1:
        EasyScene();
        break;
    case 2:
        RandomScene();
        break;
    case 3:
        TwoCheckerSphereScene();
        break;
    default:
        break;
    }
    return 0;
}

void EasyScene()
{
    // Camera

    Point3 look_from(3, 3, 2);
    Point3 look_at(0, 0, -1);
    Vec3 up(0, 1, 0);
    double dist_to_focus = (look_from - look_at).length();
    double aperture = 2.0;

    Camera camera(look_from, look_at, up, 20, aspect_ratio, aperture, dist_to_focus);

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

    ray_tracer.Render();
}
void RandomScene()
{
    // Camera
    Point3 look_from(13, 2, 3);
    Point3 look_at(0, 0, 0);
    Vec3 up(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    Camera camera(look_from, look_at, up, 20, aspect_ratio, aperture, dist_to_focus);

    // Scene Setting
    auto material_ground = new Lambertian(Color(0.5, 0.5, 0.5));
    std::vector<Object *> objects;
    // objects.push_back(new Sphere(Point3(0, -1000, 0), 1000, material_ground));

    auto checker_texture = new CheckerTexture(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    objects.push_back(new Sphere(Point3(0, -1000, 0), 1000, new Lambertian(checker_texture)));

    for (int a = -11; a < 11; ++a)
    {
        for (int b = -11; b < 11; ++b)
        {
            auto choose_material = double_random();
            Point3 center(a + 0.9 * double_random(), 0.2, b + 0.9 * double_random());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {

                if (choose_material < 0.8) // diffuse
                {
                    auto albedo = vec3_random() * vec3_random();

                    objects.push_back(new Sphere(center, 0.2, new Lambertian(albedo)));
                }
                else if (choose_material < 0.95) // metal
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

    ray_tracer.Render();

    return;
}
void TwoCheckerSphereScene()
{
    // Camera
    Point3 look_from(13, 2, 3);
    Point3 look_at(0, 0, 0);
    Vec3 up(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    Camera camera(look_from, look_at, up, 20, aspect_ratio, aperture, dist_to_focus);

    auto checker_texture = new CheckerTexture(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    std::vector<Object *> objects;
    objects.push_back(new Sphere(Point3(0, -10, 0), 10, new Lambertian(checker_texture)));
    objects.push_back(new Sphere(Point3(0, 10, 0), 10, new Lambertian(checker_texture)));

    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth);

    ray_tracer.Render();
}
