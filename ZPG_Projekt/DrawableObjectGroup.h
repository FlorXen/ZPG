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

    void addDrawable(std::shared_ptr<Drawable> drawable) override;
    void setAsCameraObserver(std::shared_ptr<Camera> camera) override;

    std::vector<std::shared_ptr<Drawable>> getDrawables() override;

private:
    std::vector<std::shared_ptr<Drawable>> drawables;
    
};
