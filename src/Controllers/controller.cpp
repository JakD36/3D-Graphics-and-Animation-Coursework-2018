//
//  controller.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "Controller.hpp"

Controller::Controller(GLFWwindow* window, SceneGraph* model,Renderer* view){ // FIX: Add defensive programming make sure pointer is not null
    this->p_model = model;
    this->p_view = view;
    this->p_window = window;
    
    glfwGetCursorPos(window, &m_lastX, &m_lastY);        // Need to call this to get the position of the cursor upon starting the application, as we cannot assume its position, otherwise we get weird jumps in the camera
    
    float initYaw = 0; float initPitch = 0;
    
    this->m_sensitivity = 0.05;
    p_model->Turn(initYaw, initPitch); // Make sure the torch is facing the same direction as camera at start
    Camera* mainCamera = view->GetCamera();
    mainCamera->SetDirection(initYaw,initPitch); // point the camera in same direction as torch above
}

void Controller::ChangeScene(SceneGraph* newModel){ // FIX: Add defensive programming make sure pointer is not null
    this->p_model = newModel;
}

void Controller::SetSensitivity(GLfloat sensitivity){
    this->m_sensitivity = sensitivity; 
}

GLfloat Controller::GetSensitivity(){
    return m_sensitivity;
}
void Controller::ToggleCursor(){
    if(m_aimInput){
        m_aimInput = false;
        glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);    // Remove curser for FPS cam
    }
    else{
        m_aimInput = true;
        glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // Remove curser for FPS cam
    }
}

