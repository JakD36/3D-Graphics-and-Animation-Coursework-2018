//
// Created by Jack Davidson on 23/02/2020.
//

#include "MathUtils.hpp"

namespace math {
    glm::quat FromToRotation(glm::vec3 from, glm::vec3 to) noexcept
    {
        glm::vec3 normFrom = glm::normalize(from), normTo = glm::normalize(to);
        float dot = glm::dot(normFrom, normTo);
        if (dot == 1.0f) {
            return glm::quat();
        }
        if (dot < -0.999f) {
            const glm::vec3 tmp1 = glm::vec3(0.0f, 0.0f, 1.0f);
            glm::vec3 axis = glm::cross(from, tmp1);
            if (glm::length2(axis) < 0.01f) {
                const glm::vec3 tmp2 = glm::vec3(1.0f, 0.0f, 0.0f);
                axis = glm::cross(from, tmp2);
            }
            return glm::angleAxis(glm::pi<float>(), glm::normalize(axis));
        }
        glm::vec3 axis = glm::normalize(glm::cross(from, to));
        float angle = glm::acos(dot);
        return glm::normalize(glm::angleAxis(angle, axis));
    }
}