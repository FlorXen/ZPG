#include "DrawableObjectGroup.h"
#include "DrawableObject.h"

DrawableObjectGroup::DrawableObjectGroup() : material(glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4(0.8, 0.8, 0.8, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0), 32.0) {}

void DrawableObjectGroup::draw() {
    for (const auto& drawable : drawables) {

        if (auto* obj = dynamic_cast<DrawableObject*>(drawable.get())) {
            obj->getShaderProgram()->use();

            glm::mat4 combinedMatrix = transformation.getMatrix() * obj->getTransformation().getMatrix();
            std::vector<std::shared_ptr<TransformOperation>> combinedVectors = transformation.transformations;
            combinedVectors.insert(combinedVectors.end(), obj->getTransformation().transformations.begin(), obj->getTransformation().transformations.end());

            Transformation combinedTransformation;
            combinedTransformation.setMatrix(combinedMatrix);
            combinedTransformation.setTransformations(combinedVectors);

            // Send transformation matrix to shader
            obj->getShaderProgram()->setTransformation(std::make_shared<Transformation>(combinedTransformation));
            // Send lights to shader
            obj->getShaderProgram()->setLights();
            // Send textures to shader
            for (int i = 0; i < textures.size(); i++) {
                textures[i]->bind();
                if (!sendTexturesAt.empty()) {
                    int j = *sendTexturesAt.begin();

                    if (i == j) {
                        obj->getShaderProgram()->setTextures(textures.size(), i, textures[i]->getGl_textureID());
                        sendTexturesAt.erase(sendTexturesAt.begin());
                    }
                }
                textures[i]->unbind();
            }

            obj->getShaderProgram()->setMaterial(material);

            glBindVertexArray(obj->getModel()->getVAO());
            glDrawArrays(GL_TRIANGLES, 0, obj->getModel()->getVertexCount());

            // Unbind VAO
            glBindVertexArray(0);
        }
        else if (dynamic_cast<DrawableObjectGroup*>(drawable.get())) {
            drawable->draw();
        }
    }
}

Transformation& DrawableObjectGroup::getTransformation() {
    return transformation;
}

void DrawableObjectGroup::addDrawable(std::shared_ptr<Drawable> drawable) {
    drawable->setAsCameraObserver(camera);
    for (std::shared_ptr<LightSource> light : lightSources) {
        drawable->setAsLightSourceObserver(light);
    }
    drawables.push_back(drawable);
}

void DrawableObjectGroup::setAsCameraObserver(std::shared_ptr<Camera> camera) {
    this->camera = camera;
}

void DrawableObjectGroup::setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) {
    this->lightSources.push_back(lightSource);
}

std::vector<std::shared_ptr<Drawable>> DrawableObjectGroup::getDrawables() {
    return drawables;
}

void DrawableObjectGroup::setMaterial(const Material& material) {
    this->material = material;

    for (const auto& drawable : drawables) {
        drawable->setMaterial(material);
    }
}

void DrawableObjectGroup::addTexture(std::shared_ptr<Texture> texture) {
    textures.push_back(texture);
    this->sendTexturesAt.insert(textures.size());

    for (const auto& drawable : drawables) {
        drawable->addTexture(texture);
    }
}
