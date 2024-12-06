#pragma once
#define GLM_ENABLE_EXPERIMENTAL
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
#include "Texture.h"
#include "Skybox.h"

class Scene : public std::enable_shared_from_this<Scene> {
public:

    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::vector<std::shared_ptr<MyApp::Model>> models;
    std::vector<std::shared_ptr<Texture>> textures;
    glm::vec4 globalAmbient;

    std::vector<std::shared_ptr<Drawable>> objects;
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<LightSource>> lightSources;
    std::shared_ptr<Skybox> skybox;

    int nextObjectID = 1;
    std::shared_ptr<Drawable> select = nullptr;

    Scene();
    Scene(glm::vec4 globalAmbient);
    void AddLightSource(std::shared_ptr<LightSource> lightSource);
    void CreateObject(std::shared_ptr<Drawable> obj);
    void AddShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);
    void AddModel(std::shared_ptr<MyApp::Model> model);
    void AddTexture(std::shared_ptr<Texture> texture);
    void Render();
    void setSkybox(std::shared_ptr<Skybox> skybox);
    void setGlobalAmbient(glm::vec4 globalAmbient);
	int getNextObjectID();
	void setSelect(int ID);
	void deleteSelected();
	void pasteSelected(glm::vec3 position);
    void moveSelected(std::vector<glm::vec3> controlPoints);
};
