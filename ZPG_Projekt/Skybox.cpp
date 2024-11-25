#include "Skybox.h"

Skybox::Skybox(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram) : DrawableObject(model, shaderProgram){
}

Skybox::Skybox(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Texture> texture) : DrawableObject(model, shaderProgram) {
    addTexture(texture);
}

void Skybox::draw() {
    glDisable(GL_DEPTH_TEST); //Dont do depth comparisons.
    
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

    glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
}

void Skybox::setAsCameraObserver(std::shared_ptr<Camera> camera) {
    this->camera = camera;
    this->camera->addObserver(shared_from_this());

    this->camera->addObserver(shaderProgram);
    this->shaderProgram->bindCamera(this->camera);
    this->shaderProgram->onCameraUpdate();
    
}

void Skybox::onCameraUpdate() {
    this->transformation.setPosition(this->camera->getPosition());
}

void Skybox::onLightSourceUpdate() {
}