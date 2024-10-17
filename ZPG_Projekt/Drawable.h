#pragma once

#include <glm/mat4x4.hpp>
#include "Camera.h"
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

    virtual void setAsCameraObserver(Camera *camera) = 0;
    virtual void initializeCamera(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;

    virtual Transformation& getTransformation() = 0;

    virtual ~Drawable() {}

    virtual std::vector<std::shared_ptr<Drawable>> getDrawables() {
        return {};
    }

protected:
    Transformation transformation;
};