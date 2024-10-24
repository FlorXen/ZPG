#include "DrawableObject.h"
#include "Observer.h"

#include <iostream>

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram) : model(model), shaderProgram(shaderProgram) {
}

void DrawableObject::rotate(float angle, const glm::vec3& axis) {
    transformation.addTransformation(std::make_shared<Rotate>(angle, axis));
}

void DrawableObject::translate(const glm::vec3& translation) {
    transformation.addTransformation(std::make_shared<Translate>(translation));
}

void DrawableObject::scale(const glm::vec3& scale) {
    transformation.addTransformation(std::make_shared<Scale>(scale));
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
    this->lightSource = lightSource;
    this->lightSource->addObserver(shaderProgram);
    this->shaderProgram->bindLightSource(this->lightSource);
    this->shaderProgram->onLightSourceUpdate();
}

void DrawableObject::draw() const {

    shaderProgram->use();
    
    // Send transformation matrix to shader
    shaderProgram->setModelMatrix(std::make_shared<Transformation>(transformation));
    shaderProgram->setNormalMatrix();
    
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