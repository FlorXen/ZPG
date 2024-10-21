#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram() : viewMatrix(1.0f), projectionMatrix(1.0f) {
    shaderProgram = glCreateProgram();
}

void ShaderProgram::onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    this->viewMatrix = viewMatrix;
    this->projectionMatrix = projectionMatrix;
}

void ShaderProgram::addVertexShader(std::shared_ptr<Shader> shader) {
    shader->attachShader(this->shaderProgram);
}

void ShaderProgram::addFragmentShader(std::shared_ptr<Shader> shader) {
    shader->attachShader(this->shaderProgram);
}

void ShaderProgram::compile() {
    glLinkProgram(shaderProgram);
}

void ShaderProgram::use() const {
    glUseProgram(shaderProgram);
}

void ShaderProgram::setModelMatrix(std::shared_ptr<Transformation> transformation) {
    this->modelMatrix = transformation->getMatrix();

    // Get uniform location in shader
    GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");

    // Test on -1 if not found
    if (idModelTransform == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void ShaderProgram::setViewMatrix()  const {
    // Get uniform location in shader
    GLint idModelTransform = glGetUniformLocation(shaderProgram, "viewMatrix");

    // Test on -1 if not found
    if (idModelTransform == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void ShaderProgram::setProjectionMatrix()  const {
    // Get uniform location in shader
    GLint idModelTransform = glGetUniformLocation(shaderProgram, "projectionMatrix");

    // Test on -1 if not found
    if (idModelTransform == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void ShaderProgram::setNormalMatrix() {

    this->normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

    // Get uniform location in shader
    GLint idModelTransform = glGetUniformLocation(shaderProgram, "normalMatrix");

    // Test on -1 if not found
    if (idModelTransform == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}
