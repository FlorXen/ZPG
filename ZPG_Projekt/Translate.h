#pragma once

#include "TransformOperation.h"

class Translate : public TransformOperation {
    glm::vec3 translation;
public:
    Translate(const glm::vec3& translation) : translation(translation) {}

    void apply(glm::mat4& modelMatrix) const override {
        modelMatrix = glm::translate(modelMatrix, translation);
    }
};

