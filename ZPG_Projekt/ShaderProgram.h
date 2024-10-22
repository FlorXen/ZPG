#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <memory>
#include "Observer.h"
#include "Transformation.h"
#include "Camera.h"
#include "ShaderLoader.h"

class Shader;

//Shader program má mít kameru a observer nebude pøedávat matice ale jenom upozoròovat

class ShaderProgram : public Observer
{
private:
    GLuint shaderProgram;
    std::shared_ptr<Transformation> transformation;
    std::shared_ptr<Camera> camera;
    glm::mat4 modelMatrix;
    glm::mat3 normalMatrix;
    
public:
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    void bindCamera(std::shared_ptr<Camera> camera);
    void onCameraUpdate() override;

    void use() const;

    void setModelMatrix(std::shared_ptr<Transformation> transformation);
    void setViewMatrix(glm::mat4 viewMatrix) const;
    void setProjectionMatrix(glm::mat4 projectionMatrix) const;
    void setNormalMatrix();
};
