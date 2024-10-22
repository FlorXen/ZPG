#include "Scene.h"

Scene::Scene() : camera(std::make_shared<Camera>()) {
}

void Scene::AddObject(std::shared_ptr<Drawable> obj) {
    obj->setAsCameraObserver(camera);
    obj->initializeCamera();
    this->objects.push_back(obj);
}

void Scene::Render() {
    for (auto& obj : this->objects) {
        obj->draw();
    }
}
