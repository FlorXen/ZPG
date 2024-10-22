#include "Scene.h"

Scene::Scene() : camera(std::make_shared<Camera>()), lightSource(std::make_shared<LightSource>()) {
}

void Scene::CreateObject(std::shared_ptr<Drawable> obj) {
    obj->setAsCameraObserver(camera);
    obj->setAsLightSourceObserver(lightSource);
    this->objects.push_back(obj);
}

void Scene::AddShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) {
    this->shaders.push_back(shaderProgram);
}

void Scene::AddModel(std::shared_ptr<MyApp::Model> model) {
    this->models.push_back(model);
}

void Scene::Render() {
    for (auto& obj : this->objects) {
        obj->draw();
    }
}
