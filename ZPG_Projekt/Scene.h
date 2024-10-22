#pragma once

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <memory>
#include <vector>
#include "Drawable.h"
#include "Model.h"

class Scene : public std::enable_shared_from_this<Scene> {
public:

    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::vector<std::shared_ptr<MyApp::Model>> models;

    std::vector<std::shared_ptr<Drawable>> objects;
    std::shared_ptr<Camera> camera;

    Scene();
    void CreateObject(std::shared_ptr<Drawable> obj);
    void AddShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);
    void AddModel(std::shared_ptr<MyApp::Model> model);
    void Render();
};
