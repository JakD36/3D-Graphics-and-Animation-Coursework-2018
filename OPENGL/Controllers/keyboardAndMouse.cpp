//
//  keyboardAndMouse.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "keyboardAndMouse.hpp"

keyboardAndMouse::keyboardAndMouse(GLFWwindow* window, sceneGraph* model, renderer* view):controller(window,model,view){
        glfwGetCursorPos(window, &lastX, &lastY);        // Need to call this to get the position of the cursor upon starting the application, as we cannot assume its position, otherwise we get weird jumps in the camera
}

void keyboardAndMouse::onKey(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS)
        keyStatus[key] = true;
    else if (action == GLFW_RELEASE)
        keyStatus[key] = false;
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void keyboardAndMouse::onMouseMove(GLFWwindow* window, double x, double y){
    // This is the code for a look around (FPS like) camera
    int mouseX = static_cast<int>(x); // Get the new mouse position
    int mouseY = static_cast<int>(y);
    
    GLfloat xoffset = mouseX - lastX; // get the change in the mouse position in x and y
    GLfloat yoffset = lastY - mouseY; // Reversed
    lastX = mouseX; lastY = mouseY;   // we can now set the old mouse position to the new one for the next frame
    
    xoffset *= sensitivity; yoffset *= sensitivity; // We can reduce the speed of the movement by multiplying by the fraction sensitivity, increasing this fraction will speed up movement
    
    yaw += xoffset; pitch += yoffset;               // add the modified offset to the yaw or pitch angles to get the new angle
    
    // check for pitch out of bounds otherwise screen gets flipped
    if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;
    
    model->turn(yaw, pitch);
    view->getCamera()->turnCamera(yaw, pitch);
    
}


void keyboardAndMouse::onMouseButton(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS){
            model->usePrimary();
        }
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT){
        if(action == GLFW_PRESS){
            model->useSecondary();
        }
    }
}

void keyboardAndMouse::onMouseWheel(GLFWwindow* window, double xoffset, double yoffset){
    
}
