#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "TransformOperation.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/dual_quaternion.hpp>
#include <GLFW/glfw3.h>

class DynamicBezierTranslate : public TransformOperation {
    std::vector<glm::vec3> controlPoints;
    mutable float t;
    mutable float delta;
    mutable int segmentIndex;

public:
    DynamicBezierTranslate(const std::vector<glm::vec3>& controlPoints, float delta = 0.01f)
        : controlPoints(controlPoints), t(0.0f), delta(delta), segmentIndex(0) {
    }

    glm::mat4 get() const override {
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        if (controlPoints.size() < 4) {
            return modelMatrix;
        }

        t += delta;
        if (t >= 1.0f || t <= 0.0f) {
            t = glm::clamp(t, 0.0f, 1.0f);
            segmentIndex += (delta > 0) ? 1 : -1;

            if (segmentIndex < 0) {
                segmentIndex = 0;
                delta *= -1;
            }
            else if (segmentIndex > (controlPoints.size() / 3) - 1) {
                segmentIndex = (controlPoints.size() / 3) - 1;
                delta *= -1;
            }
        }

        int startIndex = segmentIndex;
        glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
            glm::vec4(3.0, -6.0, 3.0, 0.0),
            glm::vec4(-3.0, 3.0, 0.0, 0.0),
            glm::vec4(1.0, 0.0, 0.0, 0.0));

        glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
        glm::mat4x3 B = glm::mat4x3(controlPoints[startIndex], controlPoints[startIndex + 1], controlPoints[startIndex + 2], controlPoints[startIndex + 3]);
        glm::vec3 p = parameters * A * glm::transpose(B);

        modelMatrix = glm::translate(modelMatrix, p);
        return modelMatrix;
    }
};