#include "DrawableObject.h"
#include "Observer.h"

#include <iostream>

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram) : model(model), shaderProgram(shaderProgram),
                                material(glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4(0.8, 0.8, 0.8, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0), 32.0){}

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material) : model(model), shaderProgram(shaderProgram),
                                material(material){}

Transformation& DrawableObject::getTransformation() {
    return transformation;
}

void DrawableObject::setAsCameraObserver(std::shared_ptr<Camera> camera) {
    this->camera = camera;
    this->camera->addObserver(shaderProgram);
    this->shaderProgram->bindCamera(this->camera);
    this->shaderProgram->onCameraUpdate();
}

void DrawableObject::setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) {
    
    this->lightSources.push_back(lightSource);
    lightSources[lightSources.size()-1]->addObserver(shaderProgram);
    this->shaderProgram->bindLightSource(lightSources[lightSources.size()-1]);
    this->shaderProgram->onLightSourceUpdate();
    
}

void DrawableObject::draw() const {

    shaderProgram->use();
    
    // Send transformation matrix to shader
    shaderProgram->setTransformation(std::make_shared<Transformation>(transformation));
    shaderProgram->setLights();
    shaderProgram->setTextures();
    shaderProgram->setMaterial(material);

    glBindVertexArray(model->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
    
    // Unbind VAO
    glBindVertexArray(0);

    glUseProgram(0);
}

std::shared_ptr<ShaderProgram> DrawableObject::getShaderProgram() {
    return shaderProgram;
}

std::shared_ptr<MyApp::Model> DrawableObject::getModel() {
    return model;
}

Material DrawableObject::getMaterial() {
    return material;
}

void DrawableObject::setMaterial(const Material& material) {
    this->material = material;
}