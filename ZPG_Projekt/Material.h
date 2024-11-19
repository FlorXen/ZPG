#pragma once

#include <glm/vec4.hpp>

class Material {
public:

    Material(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& light_specular, float shininess);


    glm::vec4 getAmbient() const;
    glm::vec4 getDiffuse() const;
    glm::vec4 getSpecular() const;
    float getShininess() const;

    void setAmbient(const glm::vec4& ambient);
    void setDiffuse(const glm::vec4& diffuse);
    void setSpecular(const glm::vec4& specular);
    void setShininess(float shininess);

private:
    glm::vec4 ra;
    glm::vec4 rd;
    glm::vec4 rs;
    float shininess;
};

