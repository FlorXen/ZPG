#pragma once

#include "DrawableObject.h"

class AssimpDrawableObject : public DrawableObject
{
public:

	AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
	AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material);

	void draw() override;
};

