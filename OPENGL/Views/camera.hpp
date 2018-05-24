//
//  camera.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

class camera{
protected:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    GLfloat yaw=0, pitch=0;             // the yaw and pitch angles to be calculated from the change in mouse position
public:
    camera();
    glm::vec3 getPosition();
    glm::vec3 getFront();
    GLfloat getYaw();
    GLfloat getPitch();
    void setPosition(glm::vec3 newPosition);
    void setFront(glm::vec3 newDirection);
    void turnCamera(GLfloat yaw, GLfloat pitch);
    glm::vec3 posOnSphere(float radius,float yaw,float pitch);
};


#endif /* camera_hpp */
