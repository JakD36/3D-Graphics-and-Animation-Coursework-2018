//
//  camera.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "camera.hpp"

camera::camera(){
    cameraFront = glm::vec3(0.0f,0.0f,1.0f);  // the direction the camera is facing
    cameraPos = glm::vec3(0.0f,1.6f,0.0f);    // The cameras position in the world space
}

glm::vec3 camera::getPosition(){
    return cameraPos;
}

glm::vec3 camera::getFront(){
    return cameraFront;
}

GLfloat camera::getYaw(){
    return yaw;
}
GLfloat camera::getPitch(){
    return pitch;
}

void camera::turnCamera(GLfloat yaw, GLfloat pitch){
    
    cameraFront = glm::normalize(posOnSphere(1, yaw, pitch)); // so here we use pos on sphere to get the direction the camera is facing
                                                              // and normalise the resulting vector so we just have the unit vector
}

glm::vec3 camera::posOnSphere(float radius,float yaw,float pitch){
    glm::vec3 pos;
    pos.x = radius* sin( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    pos.y = radius* sin( glm::radians(pitch) );
    pos.z = radius* cos( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    
    return pos;
}

