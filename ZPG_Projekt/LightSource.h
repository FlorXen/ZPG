#pragma once

#include "Subject.h"
#include "Transformation.h"

#define LIGHT_OFF 0
#define LIGHT_POINT 1
#define LIGHT_DIRECTION 2
#define LIGHT_SPOT 3

class LightSource : public Subject {

public:
	LightSource();

    void rotate(float angle, const glm::vec3& axis);
    void translate(const glm::vec3& translation);
    void randomDynamicTranslate(glm::vec3 startPosition, float speed, float interval, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

    void setAmbient(glm::vec4 ambient);
    glm::vec4 getAmbient();

    void setDiffuse(glm::vec4 diffuse);
    glm::vec4 getDiffuse();

    void setSpecular(glm::vec4 specular);
    glm::vec4 getSpecular();

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
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec3 attenuation;
    glm::vec3 direction;
    float spotEffect;
};

