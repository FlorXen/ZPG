#include "DrawableObject.h"
#include "Observer.h"

#include <iostream>

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram) : model(model), shaderProgram(shaderProgram),
                                material(glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4(0.8, 0.8, 0.8, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0), 32.0){ 
    this->ID = -1;
}

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, int ID) : model(model), shaderProgram(shaderProgram),
material(glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4(0.8, 0.8, 0.8, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0), 32.0) {
    this->ID = ID;
}

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material) : model(model), shaderProgram(shaderProgram),
                                material(material){
	this->ID = -1;
}

DrawableObject::DrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, int ID, Material material) : model(model), shaderProgram(shaderProgram),
material(material) {
    this->ID = ID;
}

Transformation& DrawableObject::getTransformation() {
    return transformation;
}

void DrawableObject::setAsCameraObserver(std::shared_ptr<Camera> camera) {
    this->camera = camera;
    this->camera->addObserver(shaderProgram);
    this->shaderProgram->bindCamera(this->camera);
    this->shaderProgram->onCameraUpdate();
}

void DrawableObject::setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) {
    
    this->lightSources.push_back(lightSource);
    lightSources[lightSources.size()-1]->addObserver(shaderProgram);
    this->shaderProgram->bindLightSource(lightSources[lightSources.size()-1]);
    this->shaderProgram->onLightSourceUpdate();
    
}

void DrawableObject::draw() {

    shaderProgram->use();

    shaderProgram->setMaterial(material);
    
    // Send transformation matrix to shader
    shaderProgram->setTransformation(std::make_shared<Transformation>(transformation));
    // Send lights to shader
    shaderProgram->setLights();
    // Send textures to shader
    if (!textures.empty()) {
        for (int i = 0; i < textures.size(); i++) {
            textures[i]->activate();

            shaderProgram->setTextures(textures.size(), i, textures[i]->getTextureUnit());

            glBindVertexArray(model->getVAO());
            glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

            textures[i]->deactivate();
        }
    }
    else {
        glBindVertexArray(model->getVAO());
        glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
    }
    
    // Unbind VAO
    glBindVertexArray(0);

    glUseProgram(0);
}

std::shared_ptr<ShaderProgram> DrawableObject::getShaderProgram() {
    return shaderProgram;
}

std::shared_ptr<MyApp::Model> DrawableObject::getModel() {
    return model;
}

Material DrawableObject::getMaterial() {
    return material;
}

void DrawableObject::setMaterial(const Material& material) {
    this->material = material;
}

void DrawableObject::addTexture(std::shared_ptr<Texture> texture) {
    textures.push_back(texture);
}

std::shared_ptr<Drawable> DrawableObject::clone() {
	std::shared_ptr<DrawableObject> clone = std::make_shared<DrawableObject>(model, shaderProgram, material);
	
	// Copy transformations without tralsation
    for (const auto& transformation : this->transformation.transformations) {
        if (dynamic_cast<Translate*>(transformation.get()) == nullptr) {
            clone->transformation.addTransformation(transformation);
        }
    }

	clone->textures = textures;
	return clone;
}