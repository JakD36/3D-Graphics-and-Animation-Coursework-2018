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


/*
 Camara class
 containing the cameras position and direction it is facing 
*/
class camera{
protected:
    glm::vec3 position;                 // Position of the camera in the world space
    glm::vec3 front;                    // Direction the camera is facing
    GLfloat yaw=0, pitch=0;             // The yaw and pitch angles to be calculated from the change in mouse position
public:
    camera();                                               // Default constructor
    camera(glm::vec3 position, GLfloat yaw, GLfloat pitch); // Constructor to define position and direction facing
    
    
    // Accessors
    glm::vec3 getPosition();
    glm::vec3 getFront();
    GLfloat getYaw();
    GLfloat getPitch();
    
    // Mutators 
    void setPosition(glm::vec3 newPosition);
    void setDirection(GLfloat yaw, GLfloat pitch);
    glm::vec3 posOnSphere(float radius,float yaw,float pitch);
};


#endif /* camera_hpp */
