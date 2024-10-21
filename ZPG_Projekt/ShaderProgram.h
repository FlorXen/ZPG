#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <memory>
#include "Observer.h"
#include "Transformation.h"

class Shader;

//Shader program má mít kameru a observer nebude pøedávat matice ale jenom upozoròovat

class ShaderProgram : public Observer
{
private:
    GLuint shaderProgram;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::mat3 normalMatrix;
    
public:
    ShaderProgram();

    void onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    void addVertexShader(std::shared_ptr<Shader> shader);

    void addFragmentShader(std::shared_ptr<Shader> shader);

    void compile();

    void use() const;

    void setModelMatrix(std::shared_ptr<Transformation> transformation);

    void setViewMatrix() const;

    void setProjectionMatrix() const;

    void setNormalMatrix();
};
