#pragma once

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Transformation {
private:
    glm::mat4 modelMatrix;
    glm::vec3 translation, rotation, scale;

    void extractTransformations();
public:
    Transformation();

    void reset();

    void setMatrix(glm::mat4 newMatrix);

    void relativeRotate(float angle, const glm::vec3& axis);
    void relativeTranslate(const glm::vec3& translation);
    void relativeScale(const glm::vec3& scale);

    const glm::mat4& getMatrix() const;
};
