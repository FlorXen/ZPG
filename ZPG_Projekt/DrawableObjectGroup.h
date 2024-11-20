#pragma once

#include "Drawable.h"
#include <vector>
#include <memory>
#include <set>

class DrawableObjectGroup : public Drawable {
public:
    DrawableObjectGroup();

    void draw() override;

    Transformation& getTransformation() override;

    void addDrawable(std::shared_ptr<Drawable> drawable) override;

    void setAsCameraObserver(std::shared_ptr<Camera> camera) override;
    void setAsLightSourceObserver(std::shared_ptr<LightSource> lightSource) override;

    std::vector<std::shared_ptr<Drawable>> getDrawables() override;

    void setMaterial(const Material& material) override;

    void addTexture(std::shared_ptr<Texture> texture) override;

    Material material;
    std::vector<std::shared_ptr<Texture>> textures;
    std::set<int> sendTexturesAt;

private:
    std::vector<std::shared_ptr<Drawable>> drawables;
};
