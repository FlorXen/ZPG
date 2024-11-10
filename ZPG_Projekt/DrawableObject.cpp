#include "DrawableObject.h"
#include "Observer.h"

#include <iostream>

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram) : model(model), shaderProgram(shaderProgram) {
}

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
    
    glBindVertexArray(model->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

    // Unbind VAO
    glBindVertexArray(0);
}

std::shared_ptr<ShaderProgram> DrawableObject::getShaderProgram() {
    return shaderProgram;
}

std::shared_ptr<MyApp::Model> DrawableObject::getModel() {
    return model;
}