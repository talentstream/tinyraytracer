#include "box.hpp"

Box::Box(Point3 box_min, Point3 box_max, const Material *material)
{
    box_min_ = box_min;
    box_max_ = box_max;

    planes.push_back(new XYPlane(box_min.x(), box_min.y(), box_max.x(), box_max.y(), box_min.z(), material));
    planes.push_back(new XYPlane(box_min.x(), box_min.y(), box_max.x(), box_max.y(), box_max.z(), material));

    planes.push_back(new XZPlane(box_min.x(), box_min.z(), box_max.x(), box_max.z(), box_min.y(), material));
    planes.push_back(new XZPlane(box_min.x(), box_min.z(), box_max.x(), box_max.z(), box_max.y(), material));

    planes.push_back(new YZPlane(box_min.y(), box_min.z(), box_max.y(), box_max.z(), box_min.x(), material));
    planes.push_back(new YZPlane(box_min.y(), box_min.z(), box_max.y(), box_max.z(), box_max.x(), material));
}

bool Box::Intersect(const Ray &r, double t_min, double t_max, Intersection &intersection) const
{
    Intersection temp_intersection;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (auto plane : planes)
    {
        if (plane->Intersect(r, t_min, closest_so_far, temp_intersection))
        {
            hit_anything = true;
            closest_so_far = temp_intersection.isect_time();
            intersection = temp_intersection;
        }
    }

    return hit_anything;
}