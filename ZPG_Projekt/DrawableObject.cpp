#include "DrawableObject.h"
#include "Observer.h"

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, ShaderProgram& shaderProgram) : model(model), shaderProgram(shaderProgram) {
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
    camera->addObserver(std::make_shared<ShaderProgram>(shaderProgram));
}

void DrawableObject::initializeCamera(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shaderProgram.onCameraUpdate(viewMatrix, projectionMatrix);
}

void DrawableObject::draw() const {
    shaderProgram.use();

    // Send transformation matrix to shader
    shaderProgram.setModelMatrix(transformation.getMatrix());
    shaderProgram.setViewMatrix();
    shaderProgram.setProjectionMatrix();

    glBindVertexArray(model->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

    // Unbind VAO
    glBindVertexArray(0);
}