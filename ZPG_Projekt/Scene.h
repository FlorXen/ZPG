#pragma once

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>
#include "DrawableObject.h"
#include "Drawable.h"
#include "Camera.h"

class Scene {
public:

    std::vector<std::shared_ptr<Drawable>> objects;

    Scene();
    void AddObject(std::shared_ptr<Drawable> obj);
    void Render();
    
private:
    
    Camera* camera;
};