#include "ray_tracer.hpp"

#include <chrono>
#include <iostream>
#include <algorithm>
#include <limits>

#include "camera.hpp"
#include "scene.hpp"
#include "material.hpp"

#include "../math/constant.hpp"

double clamp(double value, double min, double max);
void Print(std::ostream &out, Color pixel_color, int samples);

RayTracer::RayTracer(Scene *scene, int width, int height, int samples, int depth)
    : scene_(scene), width_(width), height_(height), samples_(samples), depth_(depth)
{
}

Color RayTracer::RayColor(const Ray &ray, int depth)
{
    if (depth <= 0)
        return Color(0, 0, 0);

    Intersection intersection;
    auto objects = scene_->objects();

    // 计算是否有物体相交
    auto closest_so_far = kinfinity;
    for (const auto &object : objects)
    {
        if (object->Intersect(ray, 0.001, closest_so_far, intersection))
        {
            closest_so_far = intersection.isect_time();
        }
    }

    // 如果有物体相交
    if (!intersection.miss())
    {
        Ray scattered;
        Color attenuation;
        if (intersection.material()->Scatter(ray, intersection, attenuation, scattered))
            return attenuation * RayColor(scattered, depth - 1);
        return Color(0, 0, 0);
    }

    // 默认背景色
    Vec3 unit_direction = unit_vector(ray.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

void RayTracer::Render()
{
    auto begin = std::chrono::high_resolution_clock::now();

    // 开始渲染

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
                Ray r = scene_->camera()->GetRay(u, v);
                pixel_color += RayColor(r, depth_);
            }

            Print(std::cout, pixel_color, samples_);
        }
    }

    std::cerr << "\n Render Done.\n";

    //  结束渲染

    auto end = std::chrono::high_resolution_clock::now();

    auto seconds = std::chrono::duration<double>(end - begin).count();
    std::cerr << "Time: " << seconds << "s\n";
}

double clamp(double value, double min, double max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

void Print(std::ostream &out, Color pixel_color, int samples)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    double scale = 1.0 / samples;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
}
