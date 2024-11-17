#include "Transformation.h"

Transformation::Transformation() : modelMatrix(1.0f), position(glm::vec3(0.0, 0.0, 0.0)) {
}

void Transformation::reset() {
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::addTransformation(std::shared_ptr<TransformOperation> transformation) {
    transformations.push_back(transformation);
    transformation->apply(modelMatrix);
}

void Transformation::setTransformations(std::vector<std::shared_ptr<TransformOperation>> transformations) {
    this->transformations = transformations;
}

void Transformation::setPosition(glm::vec3 position) {
    this->position = position;
}

std::shared_ptr<TransformOperation> Transformation::getTransformation(int transforamtionIndex) {
    if (transforamtionIndex >= 0 && transforamtionIndex < transformations.size()) {
        return transformations[transforamtionIndex];
    }
    else
        return nullptr;
}

void Transformation::updateTransformations() {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix[3].x = position.x;
    modelMatrix[3].y = position.y;
    modelMatrix[3].z = position.z;

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
