#pragma once

#include "TransformOperation.h"

class Translate : public TransformOperation {
    glm::vec3 translation;
public:
    Translate(const glm::vec3& translation) : translation(translation) {}

    glm::mat4 get() const override {
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        modelMatrix = glm::translate(modelMatrix, translation);

        return modelMatrix;
    }
};

