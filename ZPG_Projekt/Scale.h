#pragma once

#include "TransformOperation.h"

class Scale : public TransformOperation {
    glm::vec3 scale;
public:
    Scale(const glm::vec3& scale) : scale(scale) {}

    glm::mat4 get() const override {
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        modelMatrix = glm::scale(modelMatrix, scale);

        return modelMatrix;
    }
};

