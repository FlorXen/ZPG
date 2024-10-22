#pragma once

#include <memory>

#include "Model.h"
#include "ShaderProgram.h"
#include "Drawable.h"

class DrawableObject : public Drawable{
public:
    DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram);

    void rotate(float angle, const glm::vec3& axis) override;
    void translate(const glm::vec3& translation) override;
    void scale(const glm::vec3& scale) override;

    Transformation& getTransformation() override;

    void setAsCameraObserver(std::shared_ptr<Camera> camera) override;
    void setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) override;

    void draw() const override;

    std::shared_ptr<ShaderProgram> getShaderProgram();
    std::shared_ptr<MyApp::Model> getModel();
    
private:
    std::shared_ptr<MyApp::Model> model;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Transformation transformation;
};
