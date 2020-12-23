//
//  Camera.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "Camera.hpp"
#include <glm/gtx/transform.hpp>
#include "../../Utils/VectorUtils.hpp"
#include "../../Utils/DebugUtils.h"

// Constructors
Camera::Camera() noexcept{
    m_position = glm::vec3(0.0f,1.6f,0.0f);    // The cameras position in the world space
    m_rotation = glm::quat();
    m_up = glm::vec3(0.0f,1.0f,0.0f);

    m_forward = m_rotation * glm::vec3(0.0f,0.0f,1.0f);
    m_fov = glm::radians(50.0f);

    m_closeClipPlane = 0.1f;
    m_farClipPlane = 1000.0f;
    m_aspect = 16.0f/9.0f;
    m_projMatrix = glm::perspective(m_fov, m_aspect, m_closeClipPlane, m_farClipPlane);
}

Camera::Camera(glm::vec3 position, glm::quat rotation, glm::vec3 upVec) noexcept{
    assertm(upVec!=glm::vec3(),"Camera Up was provided a zero vector.");
    m_position = position;
    m_rotation = rotation;
    m_up = upVec;

    m_forward = m_rotation * glm::vec3(0.0f,0.0f,1.0f);
    m_fov = glm::radians(50.0f);

    m_closeClipPlane = 0.1f;
    m_farClipPlane = 1000.0f;
    m_aspect = 16.0f/9.0f;
    m_projMatrix =  glm::perspective(m_fov, m_aspect, m_closeClipPlane, m_farClipPlane);
    m_projMatrixDirty = false;
}

Camera::Camera(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 upVec) noexcept
{
    assertm(upVec!=glm::vec3(),"Camera Up was provided a zero vector.");
    m_position = position;
    m_rotation = glm::quat(eulerAngles);
    m_up = upVec;

    m_forward = m_rotation * glm::vec3(0.0f,0.0f,1.0f);
    m_fov = glm::radians(50.0f);

    m_closeClipPlane = 0.1f;
    m_farClipPlane = 1000.0f;
    m_aspect = 16.0f/9.0f;
    m_projMatrix =  glm::perspective(m_fov, m_aspect, m_closeClipPlane, m_farClipPlane);
    m_projMatrixDirty = false;
}

// Accessors
glm::vec3 Camera::GetPosition() noexcept{
    return m_position;
}

glm::vec3 Camera::GetForward() noexcept{
    return m_forward;
}

glm::mat4 Camera::BuildViewMat() noexcept
{
    return glm::lookAt(m_position, m_position + m_forward, m_up);
}

glm::mat4 Camera::ProjectionMatrix() noexcept
{
    if(m_projMatrixDirty)
    {
        m_projMatrix = glm::perspective(m_fov, m_aspect, m_closeClipPlane, m_farClipPlane);
    }
    return m_projMatrix;
}

void Camera::SetPosition(glm::vec3 newPosition) noexcept{
    this->m_position = newPosition;
}

void Camera::LookAt(glm::vec3 target) noexcept // TODO: Fix the calculation of the rotation quaternion
{
    m_forward = glm::normalize(target - m_position);
    const glm::vec3 fd = glm::vec3(0.0f,0.0f,1.0f);
    m_rotation = Utils::FromToRotation(fd, m_forward);
    m_forward = fd * m_rotation;
}

void Camera::SetDirection(float yaw, float pitch) noexcept{

    m_forward = glm::quat(glm::vec3(glm::radians(pitch),glm::radians(yaw),0.0f)) * glm::vec3(0.0f,0.0f,1.0f);
}