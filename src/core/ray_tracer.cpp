#include "ray_tracer.hpp"

#include <chrono>
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>

#include "camera.hpp"
#include "scene.hpp"
#include "../object/sphere.hpp"

const double infinity = std::numeric_limits<double>::infinity();

double clamp(double value, double min, double max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

inline double double_random()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

RayTracer::RayTracer(Scene *scene, int width, int height, int samples)
    : scene_(scene), width_(width), height_(height), samples_(samples)
{
}

Color RayTracer::ray_color(const Ray &ray, int depth)
{

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
        return 0.5 * (hit_point.normal_ + Color(1, 1, 1));

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
            pixel_color /= samples_;

            std::cout << static_cast<int>(256 * clamp(pixel_color[0], 0, 0.999)) << ' '
                      << static_cast<int>(256 * clamp(pixel_color[1], 0, 0.999)) << ' '
                      << static_cast<int>(256 * clamp(pixel_color[2], 0, 0.999)) << '\n';
        }
    }

    std::cerr << "\n Render Done.\n";

    //  End Rendering

    auto end = std::chrono::high_resolution_clock::now();

    auto seconds = std::chrono::duration<double>(end - begin).count();
    std::cerr << "Time: " << seconds << "s\n";
}

RayTracer::~RayTracer()
{
}
