#include "Transformation.h"

Transformation::Transformation() : modelMatrix(1.0f), position(glm::vec3(0.0, 0.0, 0.0)), wasChanged(false) {
}

void Transformation::reset() {
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::addTransformation(std::shared_ptr<TransformOperation> transformation) {
    transformations.push_back(transformation);
    modelMatrix *= transformation->get();
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
    glm::mat4 oldMatrix = modelMatrix;

    modelMatrix = glm::mat4(1.0f);
    modelMatrix[3].x = position.x;
    modelMatrix[3].y = position.y;
    modelMatrix[3].z = position.z;

    for (const auto& transformation : transformations) {
        modelMatrix *= transformation->get();
    }

    if (oldMatrix != modelMatrix)
        wasChanged = true;

}

void Transformation::swapTransformations(int index1, int index2) {
    if (index1 < transformations.size() && index2 < transformations.size()) {
        std::shared_ptr<TransformOperation> temp;

        temp = transformations[index1];
        transformations[index1] = transformations[index2];
        transformations[index2] = temp;
    }
    else
        printf("Transformation swap error: Index out of range.\n");
}

const glm::mat4& Transformation::getMatrix() const {
    return modelMatrix;
}

void Transformation::setMatrix(glm::mat4 matrix) {
    modelMatrix = matrix;
}
