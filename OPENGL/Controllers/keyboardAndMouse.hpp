//
//  keyboardAndMouse.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef keyboardAndMouse_hpp
#define keyboardAndMouse_hpp

#include <stdio.h>
#include "controller.hpp"

class keyboardAndMouse: public controller{
public:
    keyboardAndMouse(GLFWwindow* window, sceneGraph* model, renderer* view);
    
    virtual void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
    virtual void onMouseMove(GLFWwindow* window, double x, double y);
    virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);
    virtual void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset);
};

#endif /* keyboardAndMouse_hpp */
