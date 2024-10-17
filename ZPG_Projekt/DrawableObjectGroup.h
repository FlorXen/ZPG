#pragma once

#include "Drawable.h"
#include <vector>
#include <memory>

class DrawableObjectGroup : public Drawable {
public:
    void draw() const override;

    void rotate(float angle, const glm::vec3& axis) override;
    void translate(const glm::vec3& translation) override;
    void scale(const glm::vec3& scale) override;

    Transformation& getTransformation() override;

    void addDrawable(std::shared_ptr<Drawable> drawable);
    void setAsCameraObserver(Camera* camera) override;
    void initializeCamera(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    std::vector<std::shared_ptr<Drawable>> getDrawables() override;

private:
    std::vector<std::shared_ptr<Drawable>> drawables;
    
};
