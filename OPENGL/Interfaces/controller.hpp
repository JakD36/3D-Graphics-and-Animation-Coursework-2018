//
//  controller.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef controller_hpp
#define controller_hpp


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <stdio.h>

#include "sceneGraph.hpp"

class controller{
protected:
    sceneGraph* model;
    GLfloat sensitivity;
    double lastX = 0, lastY = 0;
    bool keyStatus[1024] = {false};  // Stores if the keys have been presed or not
public:
    controller(GLFWwindow* window, sceneGraph* model);
    
    void setSensitivity(GLfloat sensitivity);
    GLfloat getSensitivity();
    
    void changeScene(sceneGraph* newModel);
    
    void onResize(GLFWwindow* window, int w, int h);
    virtual void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
    virtual void onMouseMove(GLFWwindow* window, double x, double y) = 0;
    virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods) = 0;
    virtual void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) = 0 ;
};


#endif /* controller_hpp */
