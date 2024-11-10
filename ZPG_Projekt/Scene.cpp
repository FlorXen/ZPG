#include "Scene.h"

Scene::Scene() : camera(std::make_shared<Camera>()) {
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
    this->shaders.push_back(shaderProgram);
}

void Scene::AddModel(std::shared_ptr<MyApp::Model> model) {
    this->models.push_back(model);
}

void Scene::Render() {
    
    for (std::shared_ptr<LightSource> light : lightSources) {
        light->getTransformation().updateTransformations();
    }

    for (auto& obj : this->objects) {
        obj->getTransformation().updateTransformations();
        obj->draw();
    }
}
