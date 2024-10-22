#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <memory>
#include "Observer.h"
#include "Transformation.h"
#include "Camera.h"
#include "LightSource.h"
#include "ShaderLoader.h"

class Shader;

class ShaderProgram : public Observer
{
private:
    GLuint shaderProgram;
    std::shared_ptr<Transformation> transformation;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<LightSource> lightSource;
    glm::mat4 modelMatrix;
    glm::mat3 normalMatrix;
    
public:
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    void bindCamera(std::shared_ptr<Camera> camera);
    void onCameraUpdate() override;

    void bindLightSource(std::shared_ptr<LightSource> lightSource);
    void onLightSourceUpdate() override;

    void use() const;

    void setModelMatrix(std::shared_ptr<Transformation> transformation);
    void setViewMatrix(glm::mat4 viewMatrix) const;
    void setProjectionMatrix(glm::mat4 projectionMatrix) const;
    void setNormalMatrix();
    void setLightPosition(glm::vec3 lightPosition);
    void setViewPosition(glm::vec3 viewPosition);
};
