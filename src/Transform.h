//
// Created by Jack Davidson on 26/04/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_TRANSFORM_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_TRANSFORM_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform {
public:
    Transform* m_parent;

    glm::vec3 m_localPosition  = glm::vec3(0.f,0.f,0.f);
    glm::quat m_localRotation  = glm::quat();
    glm::vec3 m_localScale     = glm::vec3(1.f,1.f,1.f);

    glm::vec3 Position();
    glm::quat Rotation();

    glm::mat4 BuildModelMatrix();
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_TRANSFORM_H
