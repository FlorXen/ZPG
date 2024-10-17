#pragma once

#include "TransformOperation.h"

class Rotate : public TransformOperation {
    float angle;
    glm::vec3 axis;
public:
    Rotate(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

    void apply(glm::mat4& modelMatrix) const override {
        modelMatrix = glm::rotate(modelMatrix, angle, axis);
    }
};

