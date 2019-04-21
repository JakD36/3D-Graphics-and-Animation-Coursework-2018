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

#include "../Scenes/sceneGraph.hpp"
#include "../Views/camera.hpp"
#include "../Views/renderer.hpp"

/*
 Controller abstract class
 
 Methods are called through the OpenGL callbacks, these then call the methods of the scene that correspond to the actions mapped to that form of input.
 So can inherit from this class, to have different controller layouts be objects of the classes inherited from this.
*/
class controller{
protected:
    // For MVC controller requires access to the model and the view
    sceneGraph* model;
    renderer* view;
    
    GLfloat sensitivity; // The look sensitivity of this controller
    double lastX = 0, lastY = 0; // Last position in the x and y axis of the cursor
    GLfloat yaw = 0, pitch = 0; // the resulting spherical coordinates from cursor or stick movement to look in
    bool keyStatus[1024] = {false};  // Stores if the keys have been presed or not
public:
    // Constructor, always need a window, model and view for the controller to interact with so no default controller
    controller(GLFWwindow* window, sceneGraph* model, renderer* view);
    
    void setSensitivity(GLfloat sensitivity);
    GLfloat getSensitivity();
    
    void changeScene(sceneGraph* newModel); // FIX: Need to add some form of defensive programming to make sure controller is not passed a NULL pointer
    
    
    
    // pure abstract methods
    virtual void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
    virtual void onMouseMove(GLFWwindow* window, double x, double y) = 0;
    virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods) = 0;
    virtual void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) = 0 ;
};


#endif /* controller_hpp */
