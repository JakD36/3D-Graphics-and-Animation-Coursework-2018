//
//  camera.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "../Utils/VectorUtils.hpp"

/*
 Camara class
 containing the cameras position and direction it is facing 
*/
class Camera{
protected:
    glm::vec3 m_position;                 // Position of the camera in the world space
    glm::vec3 m_forward;                    // Direction the camera is facing
    GLfloat m_yaw=0, m_pitch=0;           // The yaw and pitch angles to be calculated from the change in mouse position

    GLfloat m_fov;
    glm::vec3 m_up;

public:
    Camera();                                               // Default constructor
    Camera(glm::vec3 position, GLfloat yaw, GLfloat pitch); // Constructor to define position and direction facing

    glm::vec3 GetPosition();
    glm::vec3 GetForward();
    GLfloat GetYaw();
    GLfloat GetPitch();

    void SetPosition(glm::vec3 newPosition);
    void SetDirection(GLfloat yaw, GLfloat pitch);

    glm::mat4 BuildViewMatrix();
};


#endif /* Camera_hpp */
