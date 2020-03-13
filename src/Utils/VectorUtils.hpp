#ifndef VectorUtils_hpp
#define VectorUtils_hpp

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Utils
{
    glm::quat FromToRotation(glm::vec3 from, glm::vec3 to) noexcept;
}

#endif /* VectorUtils_hpp */