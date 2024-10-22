#include "Camera.h"

Camera::Camera() : eye(glm::vec3(0.0f, 1.5f, 5.0f)),
    target(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
    alpha(1.6f), fi(-1.6f)
{
    viewMatrix = glm::lookAt(eye, eye + target, up);
    projectionMatrix = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::setPosition(const glm::vec3& position) {
    eye = position;
    
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyCameraObservers();
}

void Camera::setOrientation(float alphaAngle, float fiAngle) {

    // Gimbal lock prevention
    alpha = glm::clamp(alphaAngle, glm::radians(1.0f), glm::radians(179.0f));
    fi = fiAngle;
    target.x = sin(alpha) * cos(fi);
    target.y = cos(alpha);
    target.z = sin(alpha) * sin(fi);

    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyCameraObservers();
}

glm::mat4 Camera::getViewMatrix() const {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::moveLeft(float distance) {
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    eye -= right * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyCameraObservers();
}

void Camera::moveRight(float distance) {
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    eye += right * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyCameraObservers();
}

void Camera::moveForward(float distance) {
    // Ignore the Y component to keep movement horizontal
    glm::vec3 forward = glm::normalize(glm::vec3(target.x, 0.0f, target.z));
    //glm::vec3 forward = glm::normalize(target);
    eye += forward * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyCameraObservers();
}

void Camera::moveBackward(float distance) {
    // Ignore the Y component to keep movement horizontal
    glm::vec3 forward = glm::normalize(glm::vec3(target.x, 0.0f, target.z));
    //glm::vec3 forward = glm::normalize(target);
    eye -= forward * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyCameraObservers();
}

void Camera::moveUp(float distance) {
    eye += up * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyCameraObservers();
}

void Camera::moveDown(float distance) {
    eye -= up * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyCameraObservers();
}

float Camera::getAlpha() {
    return alpha;
}

float Camera::getFi() {
    return fi;
}
