#pragma once

#include <glm/mat4x4.hpp> // glm::mat4

class Observer {
public:
    virtual void onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
    virtual ~Observer() = default;
};
