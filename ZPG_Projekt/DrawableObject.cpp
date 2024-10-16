#include "DrawableObject.h"
#include "Observer.h"
#include <iostream>

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram) : model(model), shaderProgram(shaderProgram) {
    //shaderProgram->onCameraUpdate(glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 5.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f));
}

void DrawableObject::relativeRotate(float angle, const glm::vec3& axis) {
    transformation.relativeRotate(angle, axis);
}

void DrawableObject::relativeTranslate(const glm::vec3& translation) {
    transformation.relativeTranslate(translation);
}

void DrawableObject::relativeScale(const glm::vec3& scale) {
    transformation.relativeScale(scale);
}

void DrawableObject::setAsCameraObserver(Camera *camera) {
    camera->addObserver(shaderProgram);
}

void DrawableObject::initializeCamera(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shaderProgram->onCameraUpdate(viewMatrix, projectionMatrix);
}

void DrawableObject::draw() const {

    shaderProgram->use();
    
    // Send transformation matrix to shader
    shaderProgram->setModelMatrix(transformation.getMatrix());
    shaderProgram->setViewMatrix();
    shaderProgram->setProjectionMatrix();
    
    glBindVertexArray(model->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

    // Unbind VAO
    glBindVertexArray(0);
}