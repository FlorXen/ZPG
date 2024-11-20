#pragma once

#include <glm/mat4x4.hpp>
#include "Camera.h"
#include "LightSource.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Texture.h"

// Interface

class Drawable {
public:
    virtual void draw() = 0;

    virtual void setAsCameraObserver(std::shared_ptr<Camera> camera) = 0;
    virtual void setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) = 0;

    virtual Transformation& getTransformation() = 0;

    virtual ~Drawable() {}

    virtual std::vector<std::shared_ptr<Drawable>> getDrawables() {
        return {};
    }

    virtual void addDrawable(std::shared_ptr<Drawable> drawable) {}

    virtual void setMaterial(const Material& material) {}

    virtual void addTexture(std::shared_ptr<Texture> texture) {}

protected:
    Transformation transformation;
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<LightSource>> lightSources;
    
};