#include "aabb.hpp"

#include <tuple>

bool AABB::Hit(const Ray &ray, double t_min, double t_max) const
{
    for (int i = 0; i < 3; ++i)
    {
        auto invD = 1.0f / ray.direction()[i];
        auto t0 = (minimum_[i] - ray.origin()[i]) * invD;
        auto t1 = (maximum_[i] - ray.origin()[i]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}
