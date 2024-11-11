#pragma once

#include "Subject.h"
#include "Transformation.h"

class LightSource : public Subject {

public:
	LightSource();

    void rotate(float angle, const glm::vec3& axis);
    void translate(const glm::vec3& translation);
    void randomDynamicTranslate(glm::vec3 startPosition, float speed, float interval, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

    void setDiffuseColor(glm::vec4 diffuseColor);
    glm::vec4 getDiffuseColor();

    void setSpecularStrength(glm::vec4 specularStrength);
    glm::vec4 getSpecularStrength();

    void setAttenuation(glm::vec3 attenuation);
    glm::vec3 getAttenuation();

    glm::vec4 getPosition();
    Transformation& getTransformation();


private:

    Transformation transformation;
    glm::vec4 diffuseColor;
    glm::vec4 specularStrength;
    glm::vec3 attenuation;
};

