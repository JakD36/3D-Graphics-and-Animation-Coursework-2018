//
//  camera.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "camera.hpp"

// Constructors
camera::camera(){
    position = glm::vec3(0.0f,1.6f,0.0f);    // The cameras position in the world space
    yaw = 0; pitch = 0;
    front = posOnSphere(1, yaw, pitch);
}

camera::camera(glm::vec3 position, GLfloat yaw, GLfloat pitch){
    this->position = position;
    this->yaw; this->pitch = pitch;
    front = posOnSphere(1, yaw, pitch);
}


// Accessors
glm::vec3 camera::getPosition(){
    return position;
}

glm::vec3 camera::getFront(){
    return front;
}

GLfloat camera::getYaw(){
    return yaw;
}
GLfloat camera::getPitch(){
    return pitch;
}



// Modifiers
void camera::setPosition(glm::vec3 newPosition){
    this->position = newPosition;
}

void camera::setDirection(GLfloat yaw, GLfloat pitch){
    front = glm::normalize(posOnSphere(1, yaw, pitch)); // so here we use pos on sphere to get the direction the camera is facing
                                                              // and normalise the resulting vector to make sure we just have the unit vector
}


// Calculate the cartesian vector from the spherical coordinates
glm::vec3 camera::posOnSphere(float radius,float yaw,float pitch){
    glm::vec3 pos; // initialise the vector to be returned as (0,0,0)
    pos.x = radius * sin( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    pos.y = radius * sin( glm::radians(pitch) );
    pos.z = radius * cos( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    
    return pos;
}

