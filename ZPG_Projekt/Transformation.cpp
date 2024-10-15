#include "Transformation.h"

Transformation::Transformation() : modelMatrix(1.0f) {
}

void Transformation::reset() {
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::setMatrix(glm::mat4 newMatrix) {
    modelMatrix = newMatrix;
}

const glm::mat4& Transformation::getMatrix() const {
    return modelMatrix;
}

void Transformation::relativeRotate(float angle, const glm::vec3& axis) {
    modelMatrix = glm::rotate(modelMatrix, angle, axis);
}

void Transformation::relativeTranslate(const glm::vec3& translation) {
    modelMatrix = glm::translate(modelMatrix, translation);
}

void Transformation::relativeScale(const glm::vec3& scale) {
    modelMatrix = glm::scale(modelMatrix, scale);
}
