//
// Created by Jack Davidson on 26/04/2020.
//

#include "Transform.h"
#include <glm/gtx/transform.hpp>

glm::vec3 Transform::Position()
{
    if(m_parent != NULL)
    {
        return m_parent->Position() + m_parent->m_localRotation * m_localPosition;
    }
    return m_localPosition;
}

glm::quat Transform::Rotation()
{
    if(m_parent != NULL)
    {
        return m_parent->m_localRotation * m_localRotation;
    }
    return m_localRotation;
}

glm::mat4 Transform::BuildModelMatrix()
{
    glm::mat4 s = glm::scale(glm::mat4(1.f), m_localScale);
    glm::mat4 r = glm::toMat4(Rotation());
    glm::mat4 t = glm::translate(glm::mat4(1.f),Position());
    return t * r * s;
}