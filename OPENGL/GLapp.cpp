//
//  GLapp.cpp
//  OPENGL
//
//  Created by Jack Davidson on 26/09/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"

GLapp::GLapp(){
    if (!glfwInit()) {                            // Checking for GLFW
        cout << "Could not initialise GLFW...";
    }
    glfwSetErrorCallback(errorCallbackGLFW);    // Setup a function to catch and display all GLFW errors.
    hintsGLFW();                                // Setup glfw with various hints.
    // Start a window using GLFW
    string title = "My OpenGL Application";
    window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
    if (!window) {                                // Window or OpenGL context creation failed
        cout << "Could not initialise GLFW...";
        endProgram();
        //return 0;
    }
    
    glfwMakeContextCurrent(window);                // making the OpenGL context current
    
    // Start GLEW (note: always initialise GLEW after creating your window context.)
    glewExperimental = GL_TRUE;                    // hack: catching them all - forcing newest debug callback (glDebugMessageCallback)
    GLenum errGLEW = glewInit();
    if (GLEW_OK != errGLEW) {                    // Problems starting GLEW?
        cout << "Could not initialise GLEW...";
        endProgram();
    }
    
    //debugGL();
    
    // Setup all the message loop callbacks.
    glfwSetWindowSizeCallback(window, onResizeCallback);            // Set callback for resize
    glfwSetKeyCallback(window, onKeyCallback);                      // Set Callback for keys
    glfwSetMouseButtonCallback(window, onMouseButtonCallback);      // Set callback for mouse click
    glfwSetCursorPosCallback(window, onMouseMoveCallback);          // Set callback for mouse move
    glfwSetScrollCallback(window, onMouseWheelCallback);            // Set callback for mouse wheel.
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);    // Set mouse cursor.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // Remove curser for FPS cam
    
    glfwGetCursorPos(window, &lastX, &lastY);
    setupRender();                                // setup some render variables.
    startup();                                    // Setup all necessary information for startup (aka. load texture, shaders, models, etc).
}

void GLapp::run(){
    do {                                        // run until the window is closed
        double currentTime = glfwGetTime();     // retrieve timelapse
        glfwPollEvents();                       // poll callbacks I believe
        update(currentTime);                    // update (physics, animation, structures, etc)
        render(currentTime);                    // call render function.
        
        glfwSwapBuffers(window);                // swap buffers (avoid flickering and tearing)
        
        running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);    // exit if escape key pressed
        running &= (glfwWindowShouldClose(window) != GL_TRUE);
    } while (running);
    
    endProgram();            // Close and clean everything up...
}

void GLapp::endProgram() {
    glfwMakeContextCurrent(window);             // destroys window handler
    glfwTerminate();                            // destroys all windows and releases resources.
}

GLapp::~GLapp(){}                               //Destructor

void GLapp::classonResizeCallback(GLFWwindow* window, int w, int h) {
    windowWidth = w;
    windowHeight = h;
    
    aspect = (float)w / (float)h;
    proj_matrix = glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);
}

void GLapp::classonKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) keyStatus[key] = true;
    else if (action == GLFW_RELEASE) keyStatus[key] = false;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
}

void GLapp::classonMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS){
            LMBClicked = true;
        }
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT){
        if(action == GLFW_PRESS){
            RMBClicked = true;
        }
    }
    
}
void GLapp::classonMouseMoveCallback(GLFWwindow* window, double x, double y) {
    
    int mouseX = static_cast<int>(x);
    int mouseY = static_cast<int>(y);
    
    GLfloat xoffset = mouseX - lastX;
    GLfloat yoffset = lastY - mouseY; // Reversed
    lastX = mouseX; lastY = mouseY;
    
    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity; yoffset *= sensitivity;
    
    yaw += xoffset; pitch += yoffset;
    
    // check for pitch out of bounds otherwise screen gets flipped
    if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;
    
    
    cameraFront = glm::normalize(posOnSphere(1, yaw, pitch)); // negative the pitch if you want to invert cam in y
    
    
    torchObj.position = cameraPos + posOnSphere(sphereRadius, yaw+yawOffset, pitch - pitchOffset);

    
    torchObj.rotation.x = -pitch; // Torch seems to be backwards so has to have its pitch rotated the other way
    torchObj.rotation.y = yaw;
    lights[2].direction = cameraFront;
    
}

void GLapp::classonMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
    int yoffsetInt = static_cast<int>(yoffset);
}

glm::vec3 GLapp::posOnSphere(float radius,float yaw,float pitch){
    glm::vec3 pos;
    pos.x = radius* sin( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    pos.y = radius* sin( glm::radians(pitch) );
    pos.z = radius* cos( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    
    return pos;
}

void GLapp::printVec3(glm::vec3 vec3,string str1,string str2,string str3){
    cout<<str1<<" >> "<<vec3.x<<"\t"<<str2<<" >> "<<vec3.y<<"\t"<<str3<<" >> "<<vec3.z<<endl;
}


