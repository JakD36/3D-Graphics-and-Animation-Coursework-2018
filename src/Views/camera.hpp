//
//  camera.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../Utils/VectorUtils.hpp"

/*
 Camara class
 containing the cameras position and direction it is facing 
*/
class Camera{
protected:
    glm::vec3 m_position;                 // Position of the camera in the world space
    glm::quat m_rotation;
    glm::vec3 m_up;

    glm::vec3 m_forward;                    // Direction the camera is facing

    float m_closeClipPlane;
    float m_farClipPlane;
    float m_fov;
    float m_aspect;

    glm::mat4 m_projMatrix;

public:
    Camera();
    Camera(glm::vec3 position, glm::quat rotation, glm::vec3 upVec);
    Camera(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 upVec);

    glm::vec3 GetPosition();
    glm::vec3 GetForward();

    void SetPosition(glm::vec3 newPosition);
    void SetDirection(GLfloat yaw, GLfloat pitch);
    void LookAt(glm::vec3 target);

    glm::mat4 BuildViewMat();
    void BuildProjectionMat();
    glm::mat4 GetCachedProjMat();
};


#endif /* Camera_hpp */
