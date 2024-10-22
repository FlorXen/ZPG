#include "LightSource.h"

LightSource::LightSource() : eye(glm::vec3(0.0f, 10.0f, 0.0f)),
target(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {

}

void LightSource::setPosition(const glm::vec3& position) {
    eye = position;

    notifyLightSourceObservers();
}

glm::vec3 LightSource::getPosition() {
    return eye;
}

void LightSource::moveLeft(float distance) {
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    eye -= right * distance;
    notifyLightSourceObservers();
}

void LightSource::moveRight(float distance) {
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    eye += right * distance;
    notifyLightSourceObservers();
}

void LightSource::moveForward(float distance) {
    // Ignore the Y component to keep movement horizontal
    glm::vec3 forward = glm::normalize(glm::vec3(target.x, 0.0f, target.z));
    eye += forward * distance;
    notifyLightSourceObservers();
}

void LightSource::moveBackward(float distance) {
    // Ignore the Y component to keep movement horizontal
    glm::vec3 forward = glm::normalize(glm::vec3(target.x, 0.0f, target.z));
    eye -= forward * distance;
    notifyLightSourceObservers();
}

void LightSource::moveUp(float distance) {
    eye += up * distance;
    notifyLightSourceObservers();
}

void LightSource::moveDown(float distance) {
    eye -= up * distance;
    notifyLightSourceObservers();
}