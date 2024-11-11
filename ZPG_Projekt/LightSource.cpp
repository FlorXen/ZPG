#include "LightSource.h"

LightSource::LightSource() : diffuseColor(glm::vec4(0.385, 0.647, 0.812, 1.0)), specularStrength(glm::vec4(1.0, 1.0, 1.0, 1.0)), attenuation(glm::vec3(1.0, 0.1, 0.1)),
    direction(glm::vec3(0.0, 0.0, -1.0)), spotEffect(cos(glm::radians(8.0))) {
    this->transformation = Transformation();
}

void LightSource::rotate(float angle, const glm::vec3& axis) {
    transformation.addTransformation(std::make_shared<Rotate>(angle, axis));
    notifyLightSourceObservers();
}

void LightSource::translate(const glm::vec3& translation) {
    transformation.addTransformation(std::make_shared<Translate>(translation));
    notifyLightSourceObservers();
}

void LightSource::randomDynamicTranslate(glm::vec3 startPosition, float speed, float interval, float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    transformation.addTransformation(std::make_shared<RandomDynamicTranslate>(startPosition, speed, interval, minX, maxX, minY, maxY, minZ, maxZ));
    //notifyLightSourceObservers();
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

void LightSource::setAttenuation(glm::vec3 attenuation) {
    this->attenuation = attenuation;
}

glm::vec3 LightSource::getAttenuation() {
    return attenuation;
}

void LightSource::setLightType(int lightType) {
    this->lightType = lightType;
}

int LightSource::getLightType() {
    return lightType;
}

void LightSource::setDirection(glm::vec3 direction) {
    this->direction = direction;
}

glm::vec3 LightSource::getDirection() {
    return direction;
}

void LightSource::setSpotEffect(float angleInDegrees) {
    this->spotEffect = cos(glm::radians(angleInDegrees));
}

float LightSource::getSpotEffect() {
    return spotEffect;
}

