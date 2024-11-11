#pragma once

#include "Subject.h"
#include "Transformation.h"

#define LIGHT_OFF 0
#define LIGHT_POINT 1
#define LIGHT_DIRECTION 2
#define LIGHT_REFLECTOR 3

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

    void setLightType(int type);
    int getLightType();

    void setDirection(glm::vec3 direction);
    glm::vec3 getDirection();

    void setSpotEffect(float spotEffect);
    float getSpotEffect();



private:
    int lightType;

    Transformation transformation;
    glm::vec4 diffuseColor;
    glm::vec4 specularStrength;
    glm::vec3 attenuation;
    glm::vec3 direction;
    float spotEffect;
};

