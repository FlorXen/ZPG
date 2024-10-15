#pragma once

#include <glm/mat4x4.hpp>
#include "Camera.h"
#include "ShaderProgram.h"

// Interface

class Drawable {
public:
    virtual void draw() const = 0;

    virtual void relativeRotate(float angle, const glm::vec3& axis) = 0;
    virtual void relativeTranslate(const glm::vec3& translation) = 0;
    virtual void relativeScale(const glm::vec3& scale) = 0;

    virtual void setAsCameraObserver(Camera *camera) = 0;
    virtual void initializeCamera(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;

    virtual ~Drawable() {}
};