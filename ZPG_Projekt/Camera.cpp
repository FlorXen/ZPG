#include "Camera.h"

Camera::Camera(Scene* scene) : scene(scene), eye(glm::vec3(0.0f, 0.0f, 5.0f)),
    target(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
    alpha(0.0f), fi(0.0f)
{
    viewMatrix = glm::lookAt(eye, eye + target, up);
    projectionMatrix = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::setPosition(const glm::vec3& position) {
    eye = position;
    
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers(viewMatrix, projectionMatrix);
}

void Camera::setOrientation(float alphaAngle, float fiAngle) {
    alpha = glm::clamp(alphaAngle, -glm::half_pi<float>(), glm::half_pi<float>());
    fi = fiAngle;
    target.x = sin(alpha) * cos(fi);
    target.y = cos(alpha);
    target.z = sin(alpha) * sin(fi);
    
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers(viewMatrix, projectionMatrix);
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
    notifyObservers(viewMatrix, projectionMatrix);
}

void Camera::moveRight(float distance) {
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    eye += right * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers(viewMatrix, projectionMatrix);
}

void Camera::moveForward(float distance) {
    glm::vec3 forward = glm::normalize(target);
    eye += forward * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers(viewMatrix, projectionMatrix);
}

void Camera::moveBackward(float distance) {
    glm::vec3 forward = glm::normalize(target);
    eye -= forward * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers(viewMatrix, projectionMatrix);
}

void Camera::moveUp(float distance) {
    eye += up * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers(viewMatrix, projectionMatrix);
}

void Camera::moveDown(float distance) {
    eye -= up * distance;
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notifyObservers(viewMatrix, projectionMatrix);
}