#pragma once

#include <memory>

#include "Model.h"
#include "ShaderProgram.h"
#include "Drawable.h"
#include "Material.h"
#include "Texture.h"
#include <set>
class DrawableObject : public Drawable{
public:
    DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
    DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material);

    Transformation& getTransformation() override;

    void setAsCameraObserver(std::shared_ptr<Camera> camera) override;
    void setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) override;

    void draw() override;

    std::shared_ptr<ShaderProgram> getShaderProgram();
    std::shared_ptr<MyApp::Model> getModel();
    Material getMaterial();
    void setMaterial(const Material& material) override;
    
    void addTexture(std::shared_ptr<Texture> texture) override;
    
    Material material;
    std::vector<std::shared_ptr<Texture>> textures;
    std::set<int> sendTexturesAt;

protected:
    Transformation transformation;
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<MyApp::Model> model;
    
};
