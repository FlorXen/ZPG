#pragma once

#include "Subject.h"
#include "Transformation.h"
#include "Rotate.h"
#include "Translate.h"
#include "Scale.h"

class LightSource : public Subject {

public:
	LightSource();

    void rotate(float angle, const glm::vec3& axis);
    void translate(const glm::vec3& translation);

    void setDiffuseColor(glm::vec4 diffuseColor);
    glm::vec4 getDiffuseColor();

    void setSpecularStrength(glm::vec4 specularStrength);
    glm::vec4 getSpecularStrength();

    void setAttenuation(float attenuation);
    float getAttenuation();

    glm::vec4 getPosition();
    Transformation& getTransformation();


private:

    Transformation transformation;
    glm::vec4 diffuseColor;
    glm::vec4 specularStrength;
    float attenuation;
};

