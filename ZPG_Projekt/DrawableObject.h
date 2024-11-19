#pragma once

#include <memory>

#include "Model.h"
#include "ShaderProgram.h"
#include "Drawable.h"
#include "Material.h"

class DrawableObject : public Drawable{
public:
    DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
    DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material);

    Transformation& getTransformation() override;

    void setAsCameraObserver(std::shared_ptr<Camera> camera) override;
    void setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) override;

    void draw() const override;

    std::shared_ptr<ShaderProgram> getShaderProgram();
    std::shared_ptr<MyApp::Model> getModel();
    Material getMaterial();
    void setMaterial(const Material& material);
    
private:
    std::shared_ptr<MyApp::Model> model;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Transformation transformation;
    Material material;
};
