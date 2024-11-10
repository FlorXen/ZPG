#pragma once

#include "Drawable.h"
#include <vector>
#include <memory>

class DrawableObjectGroup : public Drawable {
public:
    void draw() const override;

    Transformation& getTransformation() override;

    void addDrawable(std::shared_ptr<Drawable> drawable) override;

    void setAsCameraObserver(std::shared_ptr<Camera> camera) override;
    void setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) override;

    std::vector<std::shared_ptr<Drawable>> getDrawables() override;

private:
    std::vector<std::shared_ptr<Drawable>> drawables;
    
};
