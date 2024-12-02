#include "DrawableObjectGroup.h"
#include "DrawableObject.h"

DrawableObjectGroup::DrawableObjectGroup() : material(glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4(0.8, 0.8, 0.8, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0), 32.0) {
	this->ID = -1;
}
DrawableObjectGroup::DrawableObjectGroup(int ID) : material(glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4(0.8, 0.8, 0.8, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0), 32.0) {
	this->ID = ID;
}

void DrawableObjectGroup::draw() {
    // Aktualizace transformaèní matice skupiny
    transformation.updateTransformations();

    for (const auto& drawable : drawables) {
        if (auto* obj = dynamic_cast<DrawableObject*>(drawable.get())) {
            obj->getShaderProgram()->use();

            obj->getTransformation().updateTransformations();

            glm::mat4 combinedMatrix = transformation.getMatrix() * obj->getTransformation().getMatrix();

            Transformation combinedTransformation;
            combinedTransformation.setMatrix(combinedMatrix);

            obj->getShaderProgram()->setMaterial(material);

            obj->getShaderProgram()->setTransformation(std::make_shared<Transformation>(combinedTransformation));

            obj->getShaderProgram()->setLights();

            if (!textures.empty()) {
                for (int i = 0; i < textures.size(); i++) {
                    textures[i]->activate();

                    obj->getShaderProgram()->setTextures(textures.size(), i, textures[i]->getTextureUnit());

                    glBindVertexArray(obj->getModel()->getVAO());
                    glDrawArrays(GL_TRIANGLES, 0, obj->getModel()->getVertexCount());

                    textures[i]->deactivate();
                }
            }
            else {
                glBindVertexArray(obj->getModel()->getVAO());
                glDrawArrays(GL_TRIANGLES, 0, obj->getModel()->getVertexCount());
            }

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

    for (const auto& drawable : drawables) {
        drawable->addTexture(texture);
    }
}

std::shared_ptr<Drawable> DrawableObjectGroup::clone() {
	auto group = std::make_shared<DrawableObjectGroup>();
	group->setAsCameraObserver(camera);
	for (std::shared_ptr<LightSource> light : lightSources) {
		group->setAsLightSourceObserver(light);
	}
	group->setMaterial(material);
	for (const auto& texture : textures) {
		group->addTexture(texture);
	}
	for (const auto& drawable : drawables) {
		group->addDrawable(drawable->clone());
	}
	return group;
}
