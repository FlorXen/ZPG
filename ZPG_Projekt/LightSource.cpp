#include "LightSource.h"

LightSource::LightSource() : diffuseColor(glm::vec4(0.385, 0.647, 0.812, 1.0)), specularStrength(glm::vec4(1.0, 1.0, 1.0, 1.0)) {
    this->attenuation = 0.1f;
}

void LightSource::rotate(float angle, const glm::vec3& axis) {
    transformation.addTransformation(std::make_shared<Rotate>(angle, axis));
    notifyLightSourceObservers();
}

void LightSource::translate(const glm::vec3& translation) {
    transformation.addTransformation(std::make_shared<Translate>(translation));
    notifyLightSourceObservers();
}

glm::vec4 LightSource::getPosition() {
    glm::mat4 posVec = transformation.getMatrix();
    return posVec[3];
}

Transformation& LightSource::getTransformation() {
    return transformation;
}

void LightSource::setDiffuseColor(glm::vec4 diffuseColor) {
    this->diffuseColor = diffuseColor;
    notifyLightSourceObservers();
}

glm::vec4 LightSource::getDiffuseColor() {
    return diffuseColor;
}

void LightSource::setSpecularStrength(glm::vec4 specularStrength) {
    this->specularStrength = specularStrength;
    notifyLightSourceObservers();
}

glm::vec4 LightSource::getSpecularStrength() {
    return specularStrength;
}


void LightSource::setAttenuation(float attenuation) {
    this->attenuation = attenuation;
}

float LightSource::getAttenuation() {
    return attenuation;
}
