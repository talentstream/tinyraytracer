#ifndef _OBJECT_LIST_HPP_
#define _OBJECT_LIST_HPP_

#include "object.hpp"

#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;


class ObjectList : public Object
{
public:
    std::vector<shared_ptr<Object>> objects_;
public:
    ObjectList() {}
    ObjectList(shared_ptr<Object> object) { add(object); }
    ~ObjectList() {}

    void clear() { objects_.clear(); }
    void add(shared_ptr<Object> object) { objects_.emplace_back(object); }

    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
};

#endif /* _OBJECT_LIST_HPP_ */