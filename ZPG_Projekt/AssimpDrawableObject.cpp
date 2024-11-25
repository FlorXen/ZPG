#include "AssimpDrawableObject.h"

AssimpDrawableObject::AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram) : DrawableObject(model, shaderProgram) {}

AssimpDrawableObject::AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material) : DrawableObject(model, shaderProgram, material) {}

void AssimpDrawableObject::draw() {

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
            glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, NULL);

            textures[i]->deactivate();
        }
    }
    else {
        glBindVertexArray(model->getVAO());
        glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, NULL);
    }

    // Unbind VAO
    glBindVertexArray(0);

    glUseProgram(0);
}