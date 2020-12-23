//
//  camera.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera{
protected:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_up;

    glm::vec3 m_forward;

    float m_closeClipPlane;
    float m_farClipPlane;
    float m_fov;
    float m_aspect;

    glm::mat4 m_projMatrix;
    bool m_projMatrixDirty;

public:
    Camera() noexcept;
    Camera(glm::vec3 position, glm::quat rotation, glm::vec3 upVec) noexcept;
    Camera(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 upVec) noexcept;

    glm::vec3 GetPosition() noexcept;
    glm::vec3 GetForward() noexcept;

    void SetPosition(glm::vec3 newPosition) noexcept;
    void SetDirection(float yaw, float pitch) noexcept;
    void LookAt(glm::vec3 target) noexcept;

    glm::mat4 BuildViewMat() noexcept;
    void BuildProjectionMat() noexcept;
    glm::mat4 ProjectionMatrix() noexcept;
};


#endif /* Camera_hpp */
