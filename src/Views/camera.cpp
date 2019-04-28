//
//  Camera.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "Camera.hpp"

// Constructors
Camera::Camera(){
    m_position = glm::vec3(0.0f,1.6f,0.0f);    // The cameras position in the world space
    m_yaw = 0; m_pitch = 0;
    m_front = Utils::Spherical2Cartesian(1, m_yaw, m_pitch);
}

Camera::Camera(glm::vec3 position, GLfloat yaw, GLfloat pitch){
    this->m_position = position;
    this->m_yaw; this->m_pitch = pitch;
    m_front = Utils::Spherical2Cartesian(1, yaw, pitch);
}


// Accessors
glm::vec3 Camera::GetPosition(){
    return m_position;
}

glm::vec3 Camera::GetFront(){
    return m_front;
}

GLfloat Camera::GetYaw(){
    return m_yaw;
}
GLfloat Camera::GetPitch(){
    return m_pitch;
}



// Modifiers
void Camera::SetPosition(glm::vec3 newPosition){
    this->m_position = newPosition;
}

void Camera::SetDirection(GLfloat yaw, GLfloat pitch){
    m_front = glm::normalize(Utils::Spherical2Cartesian(1, yaw, pitch)); // so here we use pos on sphere to get the direction the camera is facing
                                                              // and normalise the resulting vector to make sure we just have the unit vector
}