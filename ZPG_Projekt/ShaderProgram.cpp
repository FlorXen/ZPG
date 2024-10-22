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
    setViewPosition(this->camera->getPosition());
}

void ShaderProgram::bindLightSource(std::shared_ptr<LightSource> lightSource) {
    this->lightSource = lightSource;
}

void ShaderProgram::onLightSourceUpdate() {
    use();
    setLightPosition(this->lightSource->getPosition());
}

void ShaderProgram::use() const {
    glUseProgram(shaderProgram);
}

void ShaderProgram::setModelMatrix(std::shared_ptr<Transformation> transformation) {
    modelMatrix = transformation->getMatrix();

    // Get uniform location in shader
    GLint idModelMatrix = glGetUniformLocation(shaderProgram, "modelMatrix");

    // Test on -1 if not found
    if (idModelMatrix == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void ShaderProgram::setViewMatrix(glm::mat4 viewMatrix)  const {
    // Get uniform location in shader
    GLint idViewMatrix = glGetUniformLocation(shaderProgram, "viewMatrix");

    // Test on -1 if not found
    if (idViewMatrix == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void ShaderProgram::setProjectionMatrix(glm::mat4 projectionMatrix)  const {
    // Get uniform location in shader
    GLint idProjectionMatrix = glGetUniformLocation(shaderProgram, "projectionMatrix");

    // Test on -1 if not found
    if (idProjectionMatrix == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix4fv(idProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void ShaderProgram::setNormalMatrix() {

    normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

    // Get uniform location in shader
    GLint idNormalMatrix = glGetUniformLocation(shaderProgram, "normalMatrix");

    // Test on -1 if not found
    if (idNormalMatrix == -1) {
        return;
    }

    // Send matrix to shader
    glUniformMatrix3fv(idNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void ShaderProgram::setLightPosition(glm::vec3 lightPosition) {
    // Get uniform location in shader
    GLint position = glGetUniformLocation(shaderProgram, "lightPosition");

    // Test on -1 if not found
    if (position == -1) {
        return;
    }

    // Send matrix to shader
    glUniform3fv(position, 1, glm::value_ptr(lightPosition));
}

void ShaderProgram::setViewPosition(glm::vec3 viewPosition) {
    // Get uniform location in shader
    GLint position = glGetUniformLocation(shaderProgram, "viewPosition");

    // Test on -1 if not found
    if (position == -1) {
        return;
    }

    // Send matrix to shader
    glUniform3fv(position, 1, glm::value_ptr(viewPosition));
}
