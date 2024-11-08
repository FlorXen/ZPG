#include "ShaderProgram.h"
#include "Shader.h"
#include <algorithm>

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
    setCamera();
}

void ShaderProgram::bindLightSource(std::shared_ptr<LightSource> lightSource) {
    if (!(std::find(lightSources.begin(), lightSources.end(), lightSource) != lightSources.end()))
        this->lightSources.push_back(lightSource);
}

void ShaderProgram::onLightSourceUpdate() {
    use();
    setLights();
}

void ShaderProgram::use() const {
    glUseProgram(shaderProgram);
}

void ShaderProgram::setTransformation(std::shared_ptr<Transformation> transformation) {

    transformation->updateTransformations();
    
    modelMatrix = transformation->getMatrix();
    // Get uniform location in shader
    GLint idModelMatrix = glGetUniformLocation(shaderProgram, "modelMatrix");
    // Test on -1 if not found
    if (idModelMatrix == -1) {
        return;
    }
    // Send matrix to shader
    glUniformMatrix4fv(idModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

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

void ShaderProgram::setCamera() {
    std::string uniformName;
    GLint position;

    // Projection Matrix
    glm::mat4 projectionMatrix = this->camera->getProjectionMatrix();
    uniformName = "projectionMatrix";
    position = glGetUniformLocation(shaderProgram, uniformName.c_str());
    if (position != -1) {
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }

    // View Matrix
    glm::mat4 viewMatrix = this->camera->getViewMatrix();
    uniformName = "viewMatrix";
    position = glGetUniformLocation(shaderProgram, uniformName.c_str());
    if (position != -1) {
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    }

    // Camera Position
    glm::vec3 cameraPosition = this->camera->getPosition();
    uniformName = "cameraPosition";
    position = glGetUniformLocation(shaderProgram, uniformName.c_str());
    if (position != -1) {
        glUniform3fv(position, 1, glm::value_ptr(cameraPosition));
    }

}

void ShaderProgram::setLights() {
    std::string uniformName;
    GLint position;
    for (int i = 0; i < lightSources.size(); i++) {

        // Position
        uniformName = "lights[" + std::to_string(i) + "].position";
        position = glGetUniformLocation(shaderProgram, uniformName.c_str());
        if (position != -1) {
            glUniform4fv(position, 1, glm::value_ptr(lightSources[i]->getPosition()));
        }
            

        // Diffuse colour
        uniformName = "lights[" + std::to_string(i) + "].diffuse_colour";
        position = glGetUniformLocation(shaderProgram, uniformName.c_str());
        if (position != -1) {
            glUniform4fv(position, 1, glm::value_ptr(lightSources[i]->getDiffuseColor()));
        }

        // Specular strength
        uniformName = "lights[" + std::to_string(i) + "].specular";
        position = glGetUniformLocation(shaderProgram, uniformName.c_str());
        if (position != -1) {
            glUniform4fv(position, 1, glm::value_ptr(lightSources[i]->getSpecularStrength()));
        }

        // Attenuation strength
        uniformName = "lights[" + std::to_string(i) + "].attenuation_strength";
        position = glGetUniformLocation(shaderProgram, uniformName.c_str());
        if (position != -1) {
            glUniform1f(position, lightSources[i]->getAttenuation());
        }
    }

    uniformName = "numberOfLights";
    position = glGetUniformLocation(shaderProgram, uniformName.c_str());
    if (position != -1) {
        glUniform1i(position, lightSources.size());
    }
}
