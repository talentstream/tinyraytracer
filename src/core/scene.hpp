#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>

#include "camera.hpp"
#include "object.hpp"

class Scene
{
private:
    Camera *camera_;
    std::vector<Object *> objects_;

public:
    Scene(Camera *camera, std::vector<Object *> objects)
        : camera_(camera), objects_(objects) {}

    Camera *camera() const { return camera_; }
    std::vector<Object *> objects() const { return objects_; }
};

#endif /* _SCENE_HPP_ */