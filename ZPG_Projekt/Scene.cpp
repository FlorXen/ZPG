#include "Scene.h"

Scene::Scene() : camera(std::make_shared<Camera>()) {
    globalAmbient = glm::vec4(0.1, 0.1, 0.1, 1);
}

Scene::Scene(glm::vec4 globalAmbient) : camera(std::make_shared<Camera>()), globalAmbient(globalAmbient) {
}

void Scene::AddLightSource(std::shared_ptr<LightSource> lightSource) {
    lightSources.push_back(lightSource);

    for (std::shared_ptr<Drawable> obj : objects) {
        obj->setAsLightSourceObserver(lightSources[lightSources.size()-1]);
    }
}

void Scene::CreateObject(std::shared_ptr<Drawable> obj) {
    obj->setAsCameraObserver(camera);
    for (std::shared_ptr<LightSource> light : lightSources) {
        obj->setAsLightSourceObserver(light);
    }
    this->objects.push_back(obj);
}

void Scene::AddShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) {
    shaderProgram->setGlobalAmbient(this->globalAmbient);
    this->shaders.push_back(shaderProgram);
}

void Scene::AddModel(std::shared_ptr<MyApp::Model> model) {
    this->models.push_back(model);
}

void Scene::AddTexture(std::shared_ptr<Texture> texture) {
    this->textures.push_back(texture);
}

void Scene::Render() {

    if (skybox != nullptr) {
        skybox->getTransformation().updateTransformations();
        skybox->draw();
    }
    
    for (std::shared_ptr<LightSource> light : lightSources) {
        light->getTransformation().updateTransformations();
    }

    for (auto& obj : this->objects) {
        obj->getTransformation().updateTransformations();
        obj->draw();
    }

    for (std::shared_ptr<LightSource> light : lightSources) {
        light->getTransformation().wasChanged = false;
    }
}

void Scene::setSkybox(std::shared_ptr<Skybox> skybox) {
    this->skybox = skybox;
    this->skybox->setAsCameraObserver(this->camera);
}

void Scene::setGlobalAmbient(glm::vec4 globalAmbient) {
    this->globalAmbient = globalAmbient;

    for (auto& shader : this->shaders) {
        shader->setGlobalAmbient(this->globalAmbient);
    }
}
