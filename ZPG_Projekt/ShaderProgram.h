#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <memory>
#include "Observer.h"

class Shader;

class ShaderProgram : public Observer
{
private:
    GLuint shaderProgram;
    
    
public:

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    ShaderProgram();

    void onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    void addVertexShader(std::shared_ptr<Shader> shader);

    void addFragmentShader(std::shared_ptr<Shader> shader);

    void compile();

    void use() const;

    void setModelMatrix(const glm::mat4& matrix) const;

    void setViewMatrix() const;

    void setProjectionMatrix() const;
};
