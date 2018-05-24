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

#include "sceneGraph.hpp"
#include "scene1.hpp"
#include "controller.hpp"
#include "keyboardAndMouse.hpp"
#include "renderer.hpp"


// VARIABLES

shaderLoader* shaderLoader::instance = NULL;

glm::vec3 lightStruct::ia = glm::vec3(0.0f,1.0f,0.2f); // we assign the static variable for the light struct out with the any functions

//glm::vec3 posOnSphere(float radius,float yaw,float pitch);
//void printVec3(glm::vec3 vec3,string str1,string str2,string str3);


// Our prototypes for functions used throughout the program, mainly the callbacks to handle user input
void errorCallbackGLFW(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow* window, double x, double y);
void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
void debugGL();
static void APIENTRY openGLDebugCallback(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         const GLvoid* userParam);


void initOpenGL();
void hintsGLFW();
void endProgram();
void render(sceneGraph* scene);


GLFWwindow*             window;                     // Window the app will be displayed in
int                     windowWidth = 640;          // width of the window
int                     windowHeight = 480;         // height of the window

glm::mat4               proj_matrix;                // Will be used in handling perspective into the scene?

controller* mycontroller;
renderer* myView;

int main()
{
    initOpenGL();
    
    
    scene1 scene; // Our model!
    
    camera* mainCamera = new camera();
    myView = new renderer(window,&scene,mainCamera,windowWidth,windowHeight); // our view
    myView->setViewport(-windowWidth*2, 0, windowWidth*4, windowHeight*2);
    
    camera* secondCam = new camera();
    renderer* secondView = new renderer(window,&scene,secondCam,windowWidth,windowHeight);
    secondView->setViewport(-windowWidth*2, -windowHeight, windowWidth*4, windowHeight*2);
    
    mycontroller = new keyboardAndMouse(window,&scene,myView); // our controller
    
    
    bool running = true;
    do {                                        // run until the window is closed
        double currentTime = glfwGetTime();     // retrieve timelapse
        glfwPollEvents();                       // poll callbacks I believe
        scene.update(currentTime);              // update (physics, animation, structures, etc)
        
        
        myView->render();
        secondView->render();
        
        
        glfwSwapBuffers(window);                // swap buffers (avoid flickering and tearing)

        running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);    // exit if escape key pressed
        running &= (glfwWindowShouldClose(window) != GL_TRUE);
    } while (running);
    
    return 0;
}



void initOpenGL(){
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
    
    glfwSwapInterval(1);    // Ony render when synced (V SYNC)
    glfwWindowHint(GLFW_SAMPLES, 32);
    glfwWindowHint(GLFW_STEREO, GL_FALSE);
}

void endProgram() {
    glfwMakeContextCurrent(window);             // destroys window handler
    glfwTerminate();                            // destroys all windows and releases resources.
}

void hintsGLFW() {
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);            // Create context in debug mode - for debug message callback
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On windows machine course uses version 4.5 on mac i need to use 4.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );
    
    // Following two lines are required for running on mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


void onResizeCallback(GLFWwindow* window, int w, int h) {
    windowWidth = w;
    windowHeight = h;
    
//    aspect = (float)w / (float)h;
//    proj_matrix = glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    mycontroller->onMouseButton(window, button, action, mods);
}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
    mycontroller->onMouseMove(window, x, y ); // So we can swap out the controller and will have no effect on the callback
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Taken from F21GA 3D Graphics and Animation Labs

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

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

