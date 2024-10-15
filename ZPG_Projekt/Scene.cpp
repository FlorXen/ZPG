#include "Scene.h"

Scene::Scene() {
    camera = new Camera(this);
}

void Scene::AddObject(std::shared_ptr<Drawable> obj) {
    this->objects.push_back(obj);
    obj->setAsCameraObserver(camera);
    obj->initializeCamera(camera->getViewMatrix(), camera->getProjectionMatrix());
}

void Scene::Render() {
    for (auto& obj : this->objects) {
        obj->draw();
    }
}
