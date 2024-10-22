#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile){

    ShaderLoader shaderLoader;
    shaderProgram = shaderLoader.loadShader(vertexFile, fragmentFile);

    if (!shaderProgram) {
        std::cerr << "ERROR: Shader Program loading failed for files: "
            << vertexFile << " and " << fragmentFile << std::endl;
    }
}

void ShaderProgram::bindCamera(std::shared_ptr<Camera> camera) {
    this->camera = camera;
}

void ShaderProgram::onCameraUpdate() {
    use();
    setViewMatrix(this->camera->getViewMatrix());
    setProjectionMatrix(this->camera->getProjectionMatrix());
}

void ShaderProgram::use() const {
    glUseProgram(shaderProgram);
}

void ShaderProgram::setModelMatrix(std::shared_ptr<Transformation> transformation) {
    modelMatrix = transformation->getMatrix();

    // Get uniform location in shader
    GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");

    // Test on -1 if not found
    if (idModelTransform == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void ShaderProgram::setViewMatrix(glm::mat4 viewMatrix)  const {
    // Get uniform location in shader
    GLint idModelTransform = glGetUniformLocation(shaderProgram, "viewMatrix");

    // Test on -1 if not found
    if (idModelTransform == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void ShaderProgram::setProjectionMatrix(glm::mat4 projectionMatrix)  const {
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

    normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

    // Get uniform location in shader
    GLint idModelTransform = glGetUniformLocation(shaderProgram, "normalMatrix");

    // Test on -1 if not found
    if (idModelTransform == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix3fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}
