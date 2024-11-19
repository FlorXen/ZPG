#pragma once

#include <GL/glew.h>
//Include SOIL 
#include <SOIL.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <memory>
#include "Observer.h"
#include "Transformation.h"
#include "Camera.h"
#include "LightSource.h"
#include "ShaderLoader.h"
#include "Material.h"

class Shader;

class ShaderProgram : public Observer
{
private:
    
    GLuint shaderProgram;
    std::shared_ptr<Camera> camera;
    glm::mat4 modelMatrix;
    glm::mat3 normalMatrix;
    std::shared_ptr<Transformation> transformation;
    
    
public:
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    void bindCamera(std::shared_ptr<Camera> camera);
    void onCameraUpdate() override;

    void bindLightSource(std::shared_ptr<LightSource> lightSource);
    void onLightSourceUpdate() override;

    void use() const;

    void setTransformation(std::shared_ptr<Transformation> transformation);
    void setLights();
    void setCamera();
    void setTextures();
    void setMaterial(const Material& material);

    std::vector<std::shared_ptr<LightSource>> lightSources;
};
