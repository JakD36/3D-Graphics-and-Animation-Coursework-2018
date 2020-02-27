//
// Created by Jack Davidson on 23/02/2020.
//

#include "VectorUtils.hpp"
namespace Utils {
    glm::quat FromToRotation(glm::vec3 vec1, glm::vec3 vec2) {
        float dot = glm::dot(vec1, vec2);
        if (dot == 1.0f) {
            return glm::quat();
        }
        glm::vec3 rotationAxis = glm::normalize(glm::cross(vec1, vec2));
        if (dot < -0.999f) {
            const glm::vec3 tmp1 = glm::vec3(0.0f, 0.0f, 1.0f);
            rotationAxis = glm::cross(vec1, tmp1);
            if (glm::length2(rotationAxis) < 0.01f) {
                const glm::vec3 tmp2 = glm::vec3(1.0f, 0.0f, 0.0f);
                rotationAxis = glm::cross(vec1, tmp2);
            }
            return glm::angleAxis(glm::pi<float>(), glm::normalize(rotationAxis));
        }

        float angle = glm::acos(dot);
        return glm::normalize(glm::angleAxis(angle, rotationAxis));
    }
}