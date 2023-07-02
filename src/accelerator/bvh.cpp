#include "bvh.hpp"

#include <algorithm>

bool BoxCompare(const Object *a, const Object *b, int axis)
{
    AABB box_a;
    AABB box_b;

    if (!a->BoundingBox(0, 0, box_a) || !b->BoundingBox(0, 0, box_b))
        std::cerr << "No bounding box in BVHNode constructor.\n";

    return box_a.minimum()[axis] < box_b.minimum()[axis];
}

BVHNode::BVHNode(std::vector<Object *> &objects, int start, int end, double time0, double time1)
{
    // 选轴、划分
    int axis = int_random(0, 2);
    if (end - start == 1)
        left_ = right_ = objects[start];
    else if (end - start == 2)
    {
        if (BoxCompare(objects[start], objects[start + 1], axis))
        {
            left_ = objects[start];
            right_ = objects[start + 1];
        }
        else
        {
            left_ = objects[start + 1];
            right_ = objects[start];
        }
    }
    else
    {
        std::sort(objects.begin() + start, objects.begin() + end, [axis](const Object *a, const Object *b)
                  { return BoxCompare(a, b, axis); });

        int mid = start + (end - start) / 2;
        left_ = new BVHNode(objects, start, mid, time0, time1);
        right_ = new BVHNode(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;

    if (!left_->BoundingBox(time0, time1, box_left) || !right_->BoundingBox(time0, time1, box_right))
        std::cerr << "No bounding box in BVHNode constructor.\n";

    box_ = SurroundingBox(box_left, box_right);
}

bool BVHNode::Intersect(const Ray &ray, double t_min, double t_max, Intersection &intersection) const
{
    // 判断BVHNode是否与光线相交，如果相交沿树的左右子树递归判断
    if (!box_.Hit(ray, t_min, t_max))
        return false;

    bool hit_left = left_->Intersect(ray, t_min, t_max, intersection);
    bool hit_right = right_->Intersect(ray, t_min, hit_left ? intersection.isect_time() : t_max, intersection);

    return hit_left || hit_right;
}

bool BVHNode::BoundingBox(double t_min, double t_max, AABB &aabb) const
{
    aabb = box_;
    return true;
}