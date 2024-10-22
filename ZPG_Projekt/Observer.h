#pragma once

#include <glm/mat4x4.hpp> // glm::mat4

class Observer {
public:
    virtual void onCameraUpdate() = 0;
    virtual void onLightSourceUpdate() = 0;
    virtual ~Observer() = default;
};
