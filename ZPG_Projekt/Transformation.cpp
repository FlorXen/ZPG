#include "Transformation.h"

Transformation::Transformation() : modelMatrix(1.0f) {
}

void Transformation::reset() {
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::addTransformation(std::shared_ptr<TransformOperation> transformation) {
    transformations.push_back(transformation);
    transformation->apply(modelMatrix);
}

std::shared_ptr<TransformOperation> Transformation::getTransformation(int transforamtionIndex) {
    if (transforamtionIndex >= 0 && transforamtionIndex < transformations.size()) {
        return transformations[transforamtionIndex];
    }
}

void Transformation::updateTransformations() {
    modelMatrix = glm::mat4(1.0f);
    for (const auto& transformation : transformations) {
        transformation->apply(modelMatrix);
    }
}

const glm::mat4& Transformation::getMatrix() const {
    return modelMatrix;
}

void Transformation::setMatrix(glm::mat4 matrix) {
    modelMatrix = matrix;
}
