//
//  KeyboardAndMouse.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "KeyboardAndMouse.hpp"

KeyboardAndMouse::KeyboardAndMouse(GLFWwindow* window, SceneGraph* model, Renderer* view): Controller(window,model,view){
}

void KeyboardAndMouse::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS)
        m_keyStatus[key] = true;
    else if (action == GLFW_RELEASE)
        m_keyStatus[key] = false;
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void KeyboardAndMouse::OnMouseMove(GLFWwindow* window, double x, double y){
    // This is the code for a look around (FPS like) camera
    int mouseX = static_cast<int>(x); // Get the new mouse position
    int mouseY = static_cast<int>(y);
    
    GLfloat xoffset = mouseX - m_lastX; // get the change in the mouse position in x and y
    GLfloat yoffset = m_lastY - mouseY; // Reversed
    m_lastX = mouseX; m_lastY = mouseY;   // we can now set the old mouse position to the new one for the next frame
    
    xoffset *= m_sensitivity; yoffset *= m_sensitivity; // We can reduce the speed of the movement by multiplying by the fraction sensitivity, increasing this fraction will speed up movement
    
    m_yaw += xoffset; m_pitch += yoffset;               // add the modified offset to the yaw or pitch angles to get the new angle
    
    // check for pitch out of bounds otherwise screen gets flipped
    if (m_pitch > 89.0f) m_pitch = 89.0f; if (m_pitch < -89.0f) m_pitch = -89.0f;
    
    p_model->Turn(m_yaw, m_pitch);
    p_view->GetCamera()->SetDirection(m_yaw, m_pitch);
    
}


void KeyboardAndMouse::OnMouseButton(GLFWwindow* window, int button, int action, int mods){
    // On left click activate primary action
    if(button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS){
            p_model->UsePrimary();
        }
    }
    // On right click activate secondary action
    if(button == GLFW_MOUSE_BUTTON_RIGHT){
        if(action == GLFW_PRESS){
            p_model->UseSecondary();
        }
    }
}

void KeyboardAndMouse::OnMouseWheel(GLFWwindow* window, double xoffset, double yoffset){
    // Blank as this does nothing
}
