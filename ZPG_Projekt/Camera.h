#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Subject.h"

class Scene;

class Camera : public Subject {
public:
    Camera(Scene* scene);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setPosition(const glm::vec3& position);
    void setOrientation(float alpha, float fi);
    void moveLeft(float distance);
    void moveRight(float distance);
    void moveForward(float distance);
    void moveBackward(float distance);
    void moveUp(float distance);
    void moveDown(float distance);

private:
    Scene* scene;

    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;

    float alpha;
    float fi;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
