//
//  keyboardAndMouse.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 22/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef KeyboardAndMouse_hpp
#define KeyboardAndMouse_hpp

#include "Controller.hpp"

class KeyboardAndMouse: public Controller{
public:
    KeyboardAndMouse(GLFWwindow* window, SceneGraph* model) noexcept;
    
    virtual void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;
    virtual void OnMouseMove(GLFWwindow* window, double x, double y) noexcept;
    virtual void OnMouseButton(GLFWwindow* window, int button, int action, int mods) noexcept;
    virtual void OnMouseWheel(GLFWwindow* window, double xoffset, double yoffset) noexcept;
};

#endif /* keyboardAndMouse_hpp */
