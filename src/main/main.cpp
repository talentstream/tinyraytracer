#include "../core/ray_tracer.hpp"
#include "../core/scene.hpp"
#include "../core/camera.hpp"

#include "../object/sphere.hpp"
#include "../object/plane.hpp"
#include "../object/box.hpp"
#include "../object/participating_media.hpp"

#include "../material/lambertian.hpp"
#include "../material/metal.hpp"
#include "../material/dielectric.hpp"
#include "../material/diffuse_light.hpp"

#include "../texture/solid_color_texture.hpp"
#include "../texture/checker_texture.hpp"
#include "../texture/perlin_noise_texture.hpp"
#include "../texture/image_texture.hpp"

#include <vector>

// Image Settings
double aspect_ratio = 16.0 / 9.0;
int image_width = 400;
int image_height = static_cast<int>(image_width / aspect_ratio);
int samples = 10;
const int depth = 500;

// Camera Settings
Point3 look_from(13, 2, 3);
Point3 look_at(0, 0, 0);
Vec3 up(0, 1, 0);
double fov = 20.0;
double dist_to_focus = 10.0;
double aperture = 0.1;

// BackGround
Color background(0.70, 0.80, 1.00);

void EasyScene();
void RandomScene();
void TwoCheckerSphereScene();
void TwoPerlinSphereScene();
void EarthScene();
void CornellBoxScene();
void CornellSmokeScene();
void FinalScene();

int main()
{
    int select_scene = 8;

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
    case 4:
        TwoPerlinSphereScene();
        break;
    case 5:
        EarthScene();
        break;
    case 6:
        CornellBoxScene();
        break;
    case 7:
        CornellSmokeScene();
        break;
    case 8:
        FinalScene();
        break;
    default:
        break;
    }

    return 0;
}

void EasyScene()
{

    Camera camera(look_from, look_at, up, fov, aspect_ratio, aperture, dist_to_focus);

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

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth, background);

    ray_tracer.Render();
}

void RandomScene()
{

    Camera camera(look_from, look_at, up, fov, aspect_ratio, aperture, dist_to_focus);

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

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth, background);

    ray_tracer.Render();

    return;
}

void TwoCheckerSphereScene()
{

    Camera camera(look_from, look_at, up, fov, aspect_ratio, aperture, dist_to_focus);

    auto checker_texture = new CheckerTexture(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    std::vector<Object *> objects;
    objects.push_back(new Sphere(Point3(0, -10, 0), 10, new Lambertian(checker_texture)));
    objects.push_back(new Sphere(Point3(0, 10, 0), 10, new Lambertian(checker_texture)));

    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth, background);

    ray_tracer.Render();
}

void TwoPerlinSphereScene()
{
    samples = 40;

    Point3 look_from(26, 3, 6);
    Point3 look_at(0, 2, 0);
    background = Color(0.0, 0.0, 0.0);

    Camera camera(look_from, look_at, up, fov, aspect_ratio, aperture, dist_to_focus);

    auto perlin_texture = new PerlinNoiseTexture(4);
    std::vector<Object *> objects;
    objects.push_back(new Sphere(Point3(0, -1000, 0), 1000, new Lambertian(perlin_texture)));
    objects.push_back(new Sphere(Point3(0, 2, 0), 2, new Lambertian(perlin_texture)));

    auto diffuse_light = new DiffuseLight(Color(4, 4, 4));
    objects.push_back(new XYPlane(3, 1, 5, 3, -2, diffuse_light));

    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth, background);

    ray_tracer.Render();
}

void EarthScene()
{
    Camera camera(look_from, look_at, up, 20, aspect_ratio, aperture, dist_to_focus);

    auto earth_texture = new ImageTexture("../../resource/earthmap.jpg");
    std::vector<Object *> objects;

    objects.push_back(new Sphere(Point3(0, 0, 0), 2, new Lambertian(earth_texture)));

    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth, background);

    ray_tracer.Render();
}

void CornellBoxScene()
{
    aspect_ratio = 1.0;
    image_width = 600;
    image_height = static_cast<int>(image_width / aspect_ratio);
    background = Color(0, 0, 0);
    look_from = Point3(278, 278, -800);
    look_at = Point3(278, 278, 0);
    fov = 40.0;
    samples = 200;

    Camera camera(look_from, look_at, up, fov, aspect_ratio, aperture, dist_to_focus);

    auto red = new Lambertian(Color(0.65, 0.05, 0.05));
    auto white = new Lambertian(Color(0.73, 0.73, 0.73));
    auto green = new Lambertian(Color(0.12, 0.45, 0.15));
    auto light = new DiffuseLight(Color(15, 15, 15));

    std::vector<Object *> objects;

    objects.push_back(new Box(Point3(130, 0, 65), Point3(295, 165, 230), white));
    objects.push_back(new Box(Point3(265, 0, 295), Point3(430, 330, 460), white));

    // x0 y0 x1 y1 z
    objects.push_back(new YZPlane(0, 0, 555, 555, 555, green));
    objects.push_back(new YZPlane(0, 0, 555, 555, 0, red));
    objects.push_back(new XZPlane(213, 227, 343, 332, 554, light));
    objects.push_back(new XZPlane(0, 0, 555, 555, 0, white));
    objects.push_back(new XZPlane(0, 0, 555, 555, 555, white));
    objects.push_back(new XYPlane(0, 0, 555, 555, 555, white));

    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth, background);

    ray_tracer.Render();
}

void CornellSmokeScene()
{
    aspect_ratio = 1.0;
    image_width = 600;
    image_height = static_cast<int>(image_width / aspect_ratio);
    background = Color(0, 0, 0);
    look_from = Point3(278, 278, -800);
    look_at = Point3(278, 278, 0);
    fov = 40.0;
    samples = 50;

    Camera camera(look_from, look_at, up, fov, aspect_ratio, aperture, dist_to_focus);

    auto red = new Lambertian(Color(0.65, 0.05, 0.05));
    auto white = new Lambertian(Color(0.73, 0.73, 0.73));
    auto green = new Lambertian(Color(0.12, 0.45, 0.15));
    auto light = new DiffuseLight(Color(7, 7, 7));

    std::vector<Object *> objects;

    // x0 y0 x1 y1 z
    objects.push_back(new YZPlane(0, 0, 555, 555, 555, green));
    objects.push_back(new YZPlane(0, 0, 555, 555, 0, red));
    objects.push_back(new XZPlane(113, 127, 443, 432, 554, light));
    objects.push_back(new XZPlane(0, 0, 555, 555, 0, white));
    objects.push_back(new XZPlane(0, 0, 555, 555, 555, white));
    objects.push_back(new XYPlane(0, 0, 555, 555, 555, white));

    auto box1 = new Box(Point3(0, 0, 0), Point3(165, 330, 165), white);

    auto box2 = new Box(Point3(0, 0, 0), Point3(165, 165, 165), white);

    objects.push_back(new ParticipatingMedia(box1, 0.01, Color(0, 0, 0)));
    objects.push_back(new ParticipatingMedia(box2, 0.01, Color(1, 1, 1)));

    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth, background);

    ray_tracer.Render();
}

void FinalScene()
{
    aspect_ratio = 1.0;
    image_width = 800;
    image_height = static_cast<int>(image_width / aspect_ratio);
    background = Color(0, 0, 0);
    look_from = Point3(478, 278, -600);
    look_at = Point3(278, 278, 0);
    fov = 40.0;
    samples = 10;

    Camera camera(look_from, look_at, up, fov, aspect_ratio, aperture, dist_to_focus);

    std::vector<Object *> objects;

    // 地板
    auto ground = new Lambertian(Color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++)
    {
        for (int j = 0; j < boxes_per_side; j++)
        {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = double_random(1, 101);
            auto z1 = z0 + w;

            objects.push_back(new Box(Point3(x0, y0, z0), Point3(x1, y1, z1), ground));
        }
    }

    // 光源

    auto light = new DiffuseLight(Color(7, 7, 7));
    objects.push_back(new XZPlane(123, 147, 423, 412, 554, new DiffuseLight(Color(7, 7, 7))));

    // 球体

    auto center1 = Point3(400, 400, 200);
    auto center2 = center1 + Vec3(30, 0, 0);
    // auto moving_sphere_material = new Lambertian(Color(0.7, 0.3, 0.1));
    // objects.push_back(new MovingSphere(center1, center2, 0, 1, 50, moving_sphere_material));

    objects.push_back(new Sphere(Point3(260, 150, 45), 50, new Dielectric(1.5)));
    objects.push_back(new Sphere(Point3(0, 150, 145), 50, new Metal(Color(0.8, 0.8, 0.9), 10.0)));

    auto boundary = new Sphere(Point3(360, 150, 145), 70, new Dielectric(1.5));
    objects.push_back(boundary);
    objects.push_back(new ParticipatingMedia(boundary, 0.2, Color(0.2, 0.4, 0.9)));


    boundary = new Sphere(Point3(0, 0, 0), 5000, new Dielectric(1.5));
    objects.push_back(new ParticipatingMedia(boundary, 0.0001, Color(1, 1, 1)));

    auto emat = new Lambertian(new ImageTexture("earthmap.jpg"));
    objects.push_back(new Sphere(Point3(400, 200, 400), 100, emat));
    auto pertext = new PerlinNoiseTexture(0.1);
    objects.push_back(new Sphere(Point3(220, 280, 300), 80, new Lambertian(pertext)));

    auto white = new Lambertian(Color(0.73, 0.73, 0.73));

    int ns = 1000;

    for (int j = 0; j < ns; j++)
    {
        objects.push_back(new Sphere(vec3_random(0, 165), 10, white));
    }
    
    Scene scene(&camera, objects);

    RayTracer ray_tracer(&scene, image_width, image_height, samples, depth, background);

    ray_tracer.Render();
}