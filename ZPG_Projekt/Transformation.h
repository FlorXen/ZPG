#pragma once

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "TransformOperation.h"
#include "Rotate.h"
#include "DynamicRotate.h"
#include "Translate.h"
#include "RandomDynamicTranslate.h"
#include "Scale.h"

#include <vector>
#include <memory>

class Transformation {
private:
    glm::mat4 modelMatrix;
    glm::vec3 position;
public:
    Transformation();

    std::vector<std::shared_ptr<TransformOperation>> transformations;

    void reset();

    void addTransformation(std::shared_ptr<TransformOperation> transformation);
    void setTransformations(std::vector<std::shared_ptr<TransformOperation>> transformations);
    void setPosition(glm::vec3 position);
    std::shared_ptr<TransformOperation> getTransformation(int transforamtionIndex);
    void updateTransformations();

    const glm::mat4& getMatrix() const;
    void setMatrix(glm::mat4 matrix);
 
    bool wasChanged;
};
