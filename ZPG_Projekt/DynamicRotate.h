#pragma once

#include "TransformOperation.h"

class DynamicRotate : public TransformOperation
{
    float angle;
    glm::vec3 axis;
public:
    DynamicRotate(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

    glm::mat4 get() const override {
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        float newAngle = (float)glfwGetTime() * angle;
        modelMatrix = glm::rotate(modelMatrix, glm::radians(newAngle), axis);

        return modelMatrix;
    }
};

