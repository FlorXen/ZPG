#include "AssimpDrawableObject.h"

AssimpDrawableObject::AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram) : DrawableObject(model, shaderProgram) {
}

AssimpDrawableObject::AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, int ID) : DrawableObject(model, shaderProgram, ID) {
}

AssimpDrawableObject::AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, Material material) : DrawableObject(model, shaderProgram, material) {
}

AssimpDrawableObject::AssimpDrawableObject(std::shared_ptr<MyApp::Model> model, std::shared_ptr<ShaderProgram> shaderProgram, int ID, Material material) : DrawableObject(model, shaderProgram, ID, material) {
}

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

std::shared_ptr<Drawable> AssimpDrawableObject::clone() {
    std::shared_ptr<AssimpDrawableObject> clone = std::make_shared<AssimpDrawableObject>(model, shaderProgram, material);

        for (const auto& transformation : this->transformation.transformations) {
            if (dynamic_cast<Rotate*>(transformation.get()) != nullptr || dynamic_cast<Scale*>(transformation.get()) != nullptr) {
                clone->transformation.addTransformation(transformation);
            }
        }

    clone->textures = textures;
    return clone;
}