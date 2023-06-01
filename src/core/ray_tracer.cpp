#include "ray_tracer.hpp"

#include <chrono>
#include <iostream>
#include "camera.hpp"

RayTracer::RayTracer(Scene *scene, Camera *camera, int width, int height)
    : scene_(scene), camera_(camera), width_(width), height_(height)
{
}

Color RayTracer::ray_color(const Ray &ray, int depth)
{

    Vec3 unit_direction = unit_vector(ray.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return 1.0 * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

void RayTracer::render()
{
    auto begin = std::chrono::high_resolution_clock::now();

    // Begin Rendering

    std::cout << "P3\n"
              << width_ << ' ' << height_ << "\n255\n";

    for (int j = height_ - 1; j >= 0; --j)
    {
        for (int i = 0; i < width_; ++i)
        {
            auto u = double(i) / (width_ - 1);
            auto v = double(j) / (height_ - 1);

            Ray r = camera_->get_ray(u, v);

            Color pixel_color = ray_color(r, 0);

            std::cout << static_cast<int>(255.999 * pixel_color[0]) << ' '
                      << static_cast<int>(255.999 * pixel_color[1]) << ' '
                      << static_cast<int>(255.999 * pixel_color[2]) << '\n';
        }
    }

    std::cerr << "\nDone.\n";

    //  End Rendering

    auto end = std::chrono::high_resolution_clock::now();

    auto seconds = std::chrono::duration<double>(end - begin).count();
    std::cerr << "Time: " << seconds << "s\n";
}

RayTracer::~RayTracer()
{
}