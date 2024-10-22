#pragma once

#include "Subject.h"

class LightSource : public Subject {

public:
	LightSource();

    void setPosition(const glm::vec3& position);
    glm::vec3 getPosition();
    void moveLeft(float distance);
    void moveRight(float distance);
    void moveForward(float distance);
    void moveBackward(float distance);
    void moveUp(float distance);
    void moveDown(float distance);

private:
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;
};

