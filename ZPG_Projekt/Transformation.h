#pragma once

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "TransformOperation.h"

#include <vector>
#include <memory>

class Transformation {
private:
    glm::mat4 modelMatrix;
    std::vector<std::shared_ptr<TransformOperation>> transformations;

public:
    Transformation();

    void reset();

    void addTransformation(std::shared_ptr<TransformOperation> transformation);
    std::shared_ptr<TransformOperation> getTransformation(int transforamtionIndex);
    void updateTransformations();

    const glm::mat4& getMatrix() const;
    void setMatrix(glm::mat4 matrix);
    
};
