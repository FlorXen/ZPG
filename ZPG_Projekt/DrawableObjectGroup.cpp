#include "DrawableObjectGroup.h"

void DrawableObjectGroup::draw() const {
    for (const auto& drawable : drawables) {
        drawable->draw();
    }
}

void DrawableObjectGroup::relativeRotate(float angle, const glm::vec3& axis) {
    for (auto& drawable : drawables) {
        drawable->relativeRotate(angle, axis);
    }
}

void DrawableObjectGroup::relativeTranslate(const glm::vec3& translation) {
    for (auto& drawable : drawables) {
        drawable->relativeTranslate(translation);
    }
}

void DrawableObjectGroup::relativeScale(const glm::vec3& scale) {
    for (auto& drawable : drawables) {
        drawable->relativeScale(scale);
    }
}

void DrawableObjectGroup::addDrawable(std::shared_ptr<Drawable> drawable) {
    drawables.push_back(drawable);
}

void DrawableObjectGroup::setAsCameraObserver(Camera* camera) {
    for (auto& drawable : drawables) {
        drawable->setAsCameraObserver(camera);
    }
}

void DrawableObjectGroup::initializeCamera(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    for (auto& drawable : drawables) {
        drawable->initializeCamera(viewMatrix, projectionMatrix);
    }
}
