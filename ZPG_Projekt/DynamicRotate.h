#pragma once

#include "TransformOperation.h"

class DynamicRotate : public TransformOperation
{
    float angle;
    glm::vec3 axis;
public:
    DynamicRotate(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

    void apply(glm::mat4& modelMatrix) const override {
        float newAngle = (float)glfwGetTime() * angle;
        modelMatrix = glm::rotate(modelMatrix, glm::radians(newAngle), axis);
    }
};

