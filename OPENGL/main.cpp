// 01_Pipeline_Interaction
// Version up to lab 1.3.


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include "GLapp.h"

// VARIABLES
GLapp* myApp;

// Functions

int main()
{
    myApp = new GLapp();
    myApp->run();
    
    delete(myApp);
    myApp = NULL;
    return 0;
}

glm::vec3 posOnSphere(float radius,float yaw,float pitch){
    glm::vec3 pos;
    pos.x = radius*sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    pos.y = radius*sin(glm::radians(pitch));
    pos.z = radius*cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    return pos;
}

void onResizeCallback(GLFWwindow* window, int w, int h) {
    myApp->classonResizeCallback(window,w,h);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    myApp->classonKeyCallback(window,key,scancode,action,mods);
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    myApp->classonMouseButtonCallback(window,button,action,mods);
}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
    myApp->classonMouseMoveCallback(window,x,y);
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
    myApp->classonMouseWheelCallback(window,xoffset,yoffset);
}


void debugGL() {
    //Output some debugging information
    cout << "VENDOR: " << (char *)glGetString(GL_VENDOR) << endl;
    cout << "VERSION: " << (char *)glGetString(GL_VERSION) << endl;
    cout << "RENDERER: " << (char *)glGetString(GL_RENDERER) << endl;
    
    // Enable Opengl Debug
    //glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)openGLDebugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
}

static void APIENTRY openGLDebugCallback(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         const GLvoid* userParam) {
    
    cout << "---------------------opengl-callback------------" << endl;
    cout << "Message: " << message << endl;
    cout << "type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            cout << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            cout << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            cout << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            cout << "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            cout << "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            cout << "OTHER";
            break;
    }
    cout << " --- ";
    
    cout << "id: " << id << " --- ";
    cout << "severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            cout << "HIGH";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            cout << "NOTIFICATION";
    }
    cout << endl;
    cout << "-----------------------------------------" << endl;
}

void errorCallbackGLFW(int error, const char* description) {
    cout << "Error GLFW: " << description << "\n";
}
