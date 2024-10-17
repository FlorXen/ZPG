#pragma once

#include "TransformOperation.h"

class Scale : public TransformOperation {
    glm::vec3 scale;
public:
    Scale(const glm::vec3& scale) : scale(scale) {}

    void apply(glm::mat4& modelMatrix) const override {
        modelMatrix = glm::scale(modelMatrix, scale);
    }
};

