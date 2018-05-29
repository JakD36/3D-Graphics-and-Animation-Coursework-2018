//
//  controller.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "controller.hpp"

controller::controller(GLFWwindow* window, sceneGraph* model,renderer* view){ // FIX: Add defensive programming make sure pointer is not null
    this->model = model;
    this->view = view;
    
    glfwGetCursorPos(window, &lastX, &lastY);        // Need to call this to get the position of the cursor upon starting the application, as we cannot assume its position, otherwise we get weird jumps in the camera
    
    float initYaw = 0; float initPitch = 0;
    
    this->sensitivity = 0.05;
    model->turn(initYaw, initPitch); // Make sure the torch is facing the same direction as camera at start
    camera* mainCamera = view->getCamera();
    mainCamera->setDirection(initYaw,initPitch); // point the camera in same direction as torch above
}

void controller::changeScene(sceneGraph* newModel){ // FIX: Add defensive programming make sure pointer is not null
    this->model = newModel;
}



void controller::setSensitivity(GLfloat sensitivity){
    this->sensitivity = sensitivity; 
}

GLfloat controller::getSensitivity(){
    return sensitivity;
}


