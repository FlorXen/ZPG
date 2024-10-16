#pragma once

#include <memory>

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Drawable.h"

class DrawableObject : public Drawable{
public:
    DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram);

    void relativeRotate(float angle, const glm::vec3& axis) override;
    void relativeTranslate(const glm::vec3& translation) override;
    void relativeScale(const glm::vec3& scale) override;
    void setAsCameraObserver(Camera *camera) override;
    void initializeCamera(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    void draw() const override;
    
private:
    std::shared_ptr<MyApp::Model> model;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Transformation transformation;
};
