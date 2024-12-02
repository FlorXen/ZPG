#pragma once

#include "DrawableObject.h"

class AssimpDrawableObject : public DrawableObject
{
public:

	AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
	AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, int ID);
	AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material);
	AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, int ID, Material material);


	void draw() override;

	std::shared_ptr<Drawable> clone() override;
};

