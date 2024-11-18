#include "Flashlight.h"

Flashlight::Flashlight(std::shared_ptr<Camera> camera) : camera(camera), LightSource() {
	this->setLightType(LIGHT_REFLECTOR);
}

void Flashlight::initializeObserver() {
	camera->addObserver(shared_from_this());
}

void Flashlight::onCameraUpdate() {
	this->getTransformation().setPosition(this->camera->getPosition());
	this->setDirection(this->camera->getTarget());
	this->getTransformation().wasChanged = true;
}

void Flashlight::onLightSourceUpdate() {}