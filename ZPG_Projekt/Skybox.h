#pragma once

#include "DrawableObject.h"

class Skybox : public DrawableObject, public Observer, public std::enable_shared_from_this<Skybox>
{
public:

	Skybox(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
	Skybox(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Texture> texture);

	void draw() override;

	void setAsCameraObserver(std::shared_ptr<Camera> camera) override;

	void onCameraUpdate() override;

	void onLightSourceUpdate() override;
};

