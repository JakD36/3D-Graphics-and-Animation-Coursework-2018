//
//  controller.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Scenes/SceneGraph.hpp"

/*
 Controller abstract class
 
 Methods are called through the OpenGL callbacks, these then call the methods of the scene that correspond to the actions mapped to that form of input.
 So can inherit from this class, to have different controller layouts be objects of the classes inherited from this.
*/
class Controller{
protected:
    // For MVC controller requires access to the model and the view
    SceneGraph* p_model;
    GLFWwindow* p_window;
    
    bool m_aimInput = true;

    GLfloat m_sensitivity; // The look sensitivity of this controller
    double m_lastX = 0, m_lastY = 0; // Last position in the x and y axis of the cursor
    GLfloat m_yaw = 0, m_pitch = 0; // the resulting spherical coordinates from cursor or stick movement to look in
    bool m_keyStatus[1024] = {false};  // Stores if the keys have been presed or not
public:
    // Constructor, always need a window, model and view for the controller to interact with so no default controller
    Controller(GLFWwindow* window, SceneGraph* model) noexcept;
    virtual ~Controller() noexcept;
    void SetSensitivity(GLfloat sensitivity) noexcept;
    GLfloat GetSensitivity() noexcept;
    
    void ChangeScene(SceneGraph* newModel) noexcept; // FIX: Need to add some form of defensive programming to make sure controller is not passed a NULL pointer
    
    void ToggleCursor() noexcept;

    // pure abstract methods
    virtual void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept = 0;
    virtual void OnMouseMove(GLFWwindow* window, double x, double y) noexcept = 0;
    virtual void OnMouseButton(GLFWwindow* window, int button, int action, int mods) noexcept = 0;
    virtual void OnMouseWheel(GLFWwindow* window, double xoffset, double yoffset) noexcept = 0 ;
};


#endif /* Controller_hpp */
