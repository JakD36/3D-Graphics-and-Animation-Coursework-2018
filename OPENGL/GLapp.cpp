//
//  GLapp.cpp
//  OPENGL
//
//  Created by Jack Davidson on 26/09/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"

GLapp::GLapp(){
    if (!glfwInit()) {                                  // Checking for GLFW
        cout << "Could not initialise GLFW...";
    }
    glfwSetErrorCallback(errorCallbackGLFW);            // Setup a function to catch and display all GLFW errors.
    hintsGLFW();                                        // Setup glfw with various hints.
    // Start a window using GLFW
    string title = "My OpenGL Application";
    window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
    if (!window) {                                      // Window or OpenGL context creation failed
        cout << "Could not initialise GLFW...";
        endProgram();
        //return 0;
    }
    
    glfwMakeContextCurrent(window);                     // making the OpenGL context current
    
    // Start GLEW (note: always initialise GLEW after creating your window context.)
    glewExperimental = GL_TRUE;                         // hack: catching them all - forcing newest debug callback (glDebugMessageCallback)
    GLenum errGLEW = glewInit();
    if (GLEW_OK != errGLEW) {                           // Problems starting GLEW?
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
    
    
    
    glfwGetCursorPos(window, &lastX, &lastY);        // Need to call this to get the position of the cursor upon starting the application, as we cannot assume its position, otherwise we get weird jumps in the camera
    
    setupRender();
    startup();              // load textures, models,lights, shaders, all of this is done in this method in the init.cpp file
    // End of constructor
}




void GLapp::run(){ // Our game loop
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
void GLapp::classonMouseMoveCallback(GLFWwindow* window, double x, double y) { // Where we will handle moving the camera and objects based on the mouse
    
    // This is the code for a look around (FPS like) camera
    int mouseX = static_cast<int>(x); // Get the new mouse position
    int mouseY = static_cast<int>(y);
    
    GLfloat xoffset = mouseX - lastX; // get the change in the mouse position in x and y
    GLfloat yoffset = lastY - mouseY; // Reversed
    lastX = mouseX; lastY = mouseY;   // we can now set the old mouse position to the new one for the next frame
    
    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity; yoffset *= sensitivity; // We can reduce the speed of the movement by multiplying by the fraction sensitivity, increasing this fraction will speed up movement
    
    yaw += xoffset; pitch += yoffset;               // add the modified offset to the yaw or pitch angles to get the new angle
    
    // check for pitch out of bounds otherwise screen gets flipped
    if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;
    
    
    cameraFront = glm::normalize(posOnSphere(1, yaw, pitch)); // so here we use pos on sphere to get the direction the camera is facing
    // and normalise the resulting vector so we just have the unit vector
    
    
    torchObj.position = cameraPos + posOnSphere(sphereRadius, yaw+yawOffset, pitch - pitchOffset); // our torchs position is based off the camera position

    
    torchObj.rotation.x = -pitch;       // Torch seems to be backwards in its model so has to have its pitch rotated the other way
    torchObj.rotation.y = yaw;
    lights[2].direction = cameraFront; // the light from the torch just goes where we are looking
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
    // Handy for debugging to find out what different vec3s are
    cout<<str1<<" >> "<<vec3.x<<"\t"<<str2<<" >> "<<vec3.y<<"\t"<<str3<<" >> "<<vec3.z<<endl;
}


