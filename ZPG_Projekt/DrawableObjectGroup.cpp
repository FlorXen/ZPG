#include "DrawableObjectGroup.h"
#include "DrawableObject.h"

void DrawableObjectGroup::draw() const {
    for (const auto& drawable : drawables) {

        if (auto* obj = dynamic_cast<DrawableObject*>(drawable.get())) {
            obj->getShaderProgram()->use();

            glm::mat4 combinedMatrix = transformation.getMatrix() * obj->getTransformation().getMatrix();

            Transformation combinedTransformation;
            combinedTransformation.setMatrix(combinedMatrix);

            // Send transformation matrix to shader
            obj->getShaderProgram()->setModelMatrix(std::make_shared<Transformation>(combinedTransformation));

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

void DrawableObjectGroup::rotate(float angle, const glm::vec3& axis) {
    transformation.addTransformation(std::make_shared<Rotate>(angle, axis));
}

void DrawableObjectGroup::translate(const glm::vec3& translation) {
    transformation.addTransformation(std::make_shared<Translate>(translation));
}

void DrawableObjectGroup::scale(const glm::vec3& scale) {
    transformation.addTransformation(std::make_shared<Scale>(scale));
}

Transformation& DrawableObjectGroup::getTransformation() {
    return transformation;
}

void DrawableObjectGroup::addDrawable(std::shared_ptr<Drawable> drawable) {
    drawable->setAsCameraObserver(camera);
    drawable->setAsLightSourceObserver(lightSource);
    drawables.push_back(drawable);
}

void DrawableObjectGroup::setAsCameraObserver(std::shared_ptr<Camera> camera) {
    this->camera = camera;
}

void DrawableObjectGroup::setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) {
    this->lightSource = lightSource;
}

std::vector<std::shared_ptr<Drawable>> DrawableObjectGroup::getDrawables() {
    return drawables;
}
