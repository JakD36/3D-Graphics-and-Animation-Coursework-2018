//
//  keyboardAndMouse.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef KeyboardAndMouse_hpp
#define KeyboardAndMouse_hpp

#include <cstdio>
#include "Controller.hpp"
#include "../Shaders/ShaderManager.h"

class KeyboardAndMouse: public Controller{
public:
    KeyboardAndMouse(GLFWwindow* window, SceneGraph* model);
    
    virtual void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
    virtual void OnMouseMove(GLFWwindow* window, double x, double y);
    virtual void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
    virtual void OnMouseWheel(GLFWwindow* window, double xoffset, double yoffset);
};

#endif /* keyboardAndMouse_hpp */
