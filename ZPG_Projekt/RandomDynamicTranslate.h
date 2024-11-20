#pragma once

#include <random>
#include <chrono>
#include "TransformOperation.h"

class RandomDynamicTranslate : public TransformOperation {
    mutable glm::vec3 currentDirection;
    float speed;
    float changeInterval;
    mutable float lastChangeTime, X = 0, Y = 0, Z = 0;
    float minX = 0, maxX = 0, minY = 0, maxY = 0, minZ = 0, maxZ = 0;
    mutable bool firstTime = true;

    mutable std::default_random_engine generator;
    mutable std::uniform_real_distribution<float> distribution;

public:
    RandomDynamicTranslate(glm::vec3 startPosition, float speed, float interval, float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
        : speed(speed), changeInterval(interval), lastChangeTime(0.0f), distribution(-1.0, 1.0), minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ) {

        // Check if start position is in range if not then set starting pos as min
        if (startPosition.x <= maxX && startPosition.x >= minX) {
            X = startPosition.x;
        }
        else {
            if (startPosition.x > maxX)
                X = maxX;
            else
                X = minX;
        }

        if (startPosition.y <= maxY && startPosition.y >= minY) {
            Y = startPosition.y;
        }
        else {
            if (startPosition.y > maxY)
                Y = maxY;
            else
                Y = minY;
        }

        if (startPosition.z <= maxZ && startPosition.z >= minZ) {
            Z = startPosition.z;
        }
        else {
            if (startPosition.z > maxZ)
                Z = maxZ;
            else
                Z = minZ;
        }

        generator.seed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());

        currentDirection = glm::normalize(glm::vec3(distribution(generator), distribution(generator), distribution(generator)));

    }

    glm::mat4 get() const override {
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastChangeTime;

        if (deltaTime > changeInterval) {
            currentDirection = glm::normalize(glm::vec3(distribution(generator), distribution(generator), distribution(generator)));
            lastChangeTime = currentTime;
        }

        glm::vec3 translation = currentDirection * speed;


        // Check if next pos is in range and if is not then reverse direction
        if (translation.x + X <= maxX && translation.x + X >= minX) {
            translation.x += X;
            X = translation.x;
        }
        else {
            translation.x = X;
            currentDirection.x *= -1.0;
        }

        if (translation.y + Y <= maxY && translation.y + Y >= minY) {
            translation.y += Y;
            Y = translation.y;
        }
        else {
            translation.y = Y;
            currentDirection.y *= -1.0;
        }

        if (translation.z + Z <= maxZ && translation.z + Z >= minZ) {
            translation.z += Z;
            Z = translation.z;
        }
        else {
            translation.z = Z;
            currentDirection.z *= -1.0;
        }

        // On first call the matrix isnt formated so original translation would apply two times
        if (firstTime) {
            firstTime = false;
            modelMatrix[3].x = X;
            modelMatrix[3].y = Y;
            modelMatrix[3].z = Z;
        }
        else
            modelMatrix = glm::translate(modelMatrix, translation);

        return modelMatrix;
    }
};




