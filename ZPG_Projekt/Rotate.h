#pragma once

#include "TransformOperation.h"

class Rotate : public TransformOperation {
    float angle;
    glm::vec3 axis;
public:
    Rotate(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

    glm::mat4 get() const override {
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);

        return modelMatrix;
    }
};

