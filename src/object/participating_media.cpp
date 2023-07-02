#include "participating_media.hpp"

bool ParticipatingMedia::Intersect(const Ray &ray, double t_min, double t_max, Intersection &intersection) const
{
    const bool enableDebug = false;
    const bool debugging = enableDebug && double_random() < 0.00001;

    Intersection intersection1, intersection2;
    if (!boundary_->Intersect(ray, -INFINITY, INFINITY, intersection1))
        return false;
    if (!boundary_->Intersect(ray, intersection1.isect_time() + 0.0001, INFINITY, intersection2))
        return false;

    if(debugging) std::cerr << "\nt0 t1 " << intersection1.isect_time() << " " << intersection2.isect_time() << "\n";

    if (intersection1.isect_time() < t_min)
        intersection1.setIsectTime(t_min);
    if (intersection2.isect_time() > t_max)
        intersection2.setIsectTime(t_max);

    if(intersection1.isect_time() >= intersection2.isect_time())
        return false;

    if(intersection1.isect_time() < 0)
        intersection1.setIsectTime(0);
    
    const auto ray_length = ray.direction().length();
    const auto distance_inside_boundary = (intersection2.isect_time() - intersection1.isect_time()) * ray_length;
    const auto hit_distance = neg_inv_density_ * log(double_random());

    if(hit_distance > distance_inside_boundary)
        return false;

    intersection.setIsectTime(intersection1.isect_time() + hit_distance / ray_length);
    intersection.setPosition(ray.at(intersection.isect_time()));

    if(debugging) std::cerr << "hit_distance = " << hit_distance << "\n"
                            << "isect_time = " << intersection.isect_time() << "\n"
                            << "isect_point = " << intersection.position() << "\n";

    intersection.setNormal(Vec3(1, 0, 0)); // arbitrary
    intersection.setFrontFace();
    intersection.setMaterial(phase_function_);

    return true;
}
