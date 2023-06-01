#include "ray_tracer.hpp"

#include <chrono>
#include <iostream>
#include <algorithm>
#include <limits>

#include "camera.hpp"
#include "scene.hpp"

const double infinity = std::numeric_limits<double>::infinity();

double clamp(double value, double min, double max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

RayTracer::RayTracer(Scene *scene, int width, int height, int samples)
    : scene_(scene), width_(width), height_(height), samples_(samples)
{
}

Color RayTracer::ray_color(const Ray &ray, int depth)
{
    if (depth <= 0)
        return Color(0, 0, 0);

    HitPoint hit_point;
    HitPoint temp_hit_point;

    auto closest_so_far = infinity;
    bool hit_anything = false;
    auto objects = scene_->objects();
    for (size_t i = 0; i != objects.size(); ++i)
    {
        if (objects[i]->hit(ray, 0.001, closest_so_far, temp_hit_point))
        {
            hit_anything = true;
            closest_so_far = temp_hit_point.t_;
            hit_point = temp_hit_point;
        }
    }

    if (hit_anything)
    {
        Point3 target = hit_point.pos_ + hit_point.normal_ + random_in_hemisphere(hit_point.normal_);
        return 0.5 * ray_color(Ray(hit_point.pos_, target - hit_point.pos_), depth - 1);
    }

    // 背景色
    Vec3 unit_direction = unit_vector(ray.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

void RayTracer::render()
{
    auto begin = std::chrono::high_resolution_clock::now();

    // Begin Rendering

    std::cerr << "\n Render Started.\n";

    std::cout << "P3\n"
              << width_ << ' ' << height_ << "\n255\n";

    for (int j = height_ - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < width_; ++i)
        {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_; ++s)
            {
                auto u = double(i + double_random()) / (width_ - 1);
                auto v = double(j + double_random()) / (height_ - 1);
                Ray r = scene_->camera()->get_ray(u, v);
                pixel_color += ray_color(r, 5);
            }

            print(std::cout, pixel_color);
        }
    }

    std::cerr << "\n Render Done.\n";

    //  End Rendering

    auto end = std::chrono::high_resolution_clock::now();

    auto seconds = std::chrono::duration<double>(end - begin).count();
    std::cerr << "Time: " << seconds << "s\n";
}

void RayTracer::print(std::ostream &out, Color pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    double scale = 1.0 / samples_;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
}
RayTracer::~RayTracer()
{
}
