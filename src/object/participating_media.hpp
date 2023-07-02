#ifndef _PARTICIPATING_MEDIA_HPP_
#define _PARTICIPATING_MEDIA_HPP_

#include "../core/object.hpp"
#include "../material/isotropic.hpp"

class ParticipatingMedia : public Object
{
public:
    Object *boundary_;
    double neg_inv_density_;
    Material *phase_function_;

public:
    ParticipatingMedia() {}
    ParticipatingMedia(Object *boundary, double density, Color color) : boundary_(boundary), neg_inv_density_(-1 / density), phase_function_(new Isotropic(color)) {}
    ParticipatingMedia(Object *boundary, double density, Material *phase_function) : boundary_(boundary), neg_inv_density_(-1 / density), phase_function_(phase_function) {}
    ~ParticipatingMedia() {}

    virtual bool Intersect(const Ray &ray, double t_min, double t_max, Intersection &intersection) const override;
    virtual bool BoundingBox(double t_min, double t_max, AABB &aabb) const override
    {
        return boundary_->BoundingBox(t_min, t_max, aabb);
    }
};

#endif /* _PARTICIPATING_MEDIA_HPP_ */