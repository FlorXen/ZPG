#pragma once

#include <glm/mat4x4.hpp>
#include "Camera.h"
#include "LightSource.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Rotate.h"
#include "Translate.h"
#include "Scale.h"

// Interface

class Drawable {
public:
    virtual void draw() const = 0;

    virtual void rotate(float angle, const glm::vec3& axis) = 0;
    virtual void translate(const glm::vec3& translation) = 0;
    virtual void scale(const glm::vec3& scale) = 0;

    virtual void setAsCameraObserver(std::shared_ptr<Camera> camera) = 0;
    virtual void setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) = 0;

    virtual Transformation& getTransformation() = 0;

    virtual ~Drawable() {}

    virtual std::vector<std::shared_ptr<Drawable>> getDrawables() {
        return {};
    }

    virtual void addDrawable(std::shared_ptr<Drawable> drawable) {}

protected:
    Transformation transformation;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<LightSource> lightSource;
};