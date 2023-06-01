#ifndef _RAY_TRACER_HPP_
#define _RAY_TRACER_HPP_

#include "../math/vec3.hpp"
#include "../math/ray.hpp"

class Scene;
class Camera;

class RayTracer
{
public:
    RayTracer(Scene *scene, int width, int height,int samples);

    Color ray_color(const Ray &ray, int depth);

    void render();

    ~RayTracer();

private:
    Scene *scene_;
    int width_;
    int height_;
    int samples_;
};

#endif /* _RAY_TRACER_HPP_ */