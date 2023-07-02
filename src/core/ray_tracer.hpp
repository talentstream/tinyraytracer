#ifndef _RAY_TRACER_HPP_
#define _RAY_TRACER_HPP_

#include "../math/vec3.hpp"
#include "../math/ray.hpp"

class Scene;
class Camera;

class RayTracer
{
public:
    RayTracer(Scene *scene, int width, int height, int samples,int depth_,Color background);

    Color RayColor(const Ray &ray, int depth);

    void Render();

    ~RayTracer() = default;

private:
    Scene *scene_;
    int width_;
    int height_;
    int samples_;
    int depth_;
    Color background_;
};

#endif /* _RAY_TRACER_HPP_ */