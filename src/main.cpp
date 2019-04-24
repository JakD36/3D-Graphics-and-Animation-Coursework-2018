// Standard libraries
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
// #include <stdlib.h>

// OpenGL - GLEW, GLFW and GLM
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

// My classes
#include "Scenes/sceneGraph.hpp"
#include "Scenes/scene1.hpp"
#include "Controllers/controller.hpp"
#include "Controllers/keyboardAndMouse.hpp"
#include "Views/renderer.hpp"


using namespace std;

// initialise Static variables
shaderLoader* shaderLoader::instance = NULL;
glm::vec3 lightStruct::ia = glm::vec3(0.0f,1.0f,0.2f); // we assign the static variable for the light struct out with the any functions


// Our prototypes for OpenGL functions used throughout the program, mainly the callbacks to handle user input
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


// Prototypes for setting up OpenGL and closing it down
void initOpenGL();
void hintsGLFW();
void endProgram();


// Global variables
GLFWwindow*             window;                     // Window the app will be displayed in
int                     windowWidth = 640;          // width of the window
int                     windowHeight = 480;         // height of the window

controller* myController; // myController is global to be accessible through the callbacks
renderer* myView; // is global to be accessible through callbacks

int main(int argc, char *argv[])
{
    // string path = argv[0];
    // cout<<getenv("PWD")<<endl;


    // Intialise the program and the scene
    initOpenGL(); // Initialise OpenGL window,
    
    
    // Using a Model view controller pattern, allows for the addition of new controllers, scenes or even a change in the renderer
    scene1 scene; // Initialise the scene i.e the model
    
    camera* mainCamera = new camera(); // Initialise the main camera, FPS camera attached to player!
    
    myView = new renderer(window,&scene,mainCamera); // Initialise our rendering object, with the scene it will render and the camera it will be using
    
    
    /*
     Was Looking into creating multiple views, using multiple renderer objects, this is easily achieved,
     however there is an issue with the glViewport for high DPI screens like the retina displays in Macs.
    */
    myView->setViewport(0, 0, windowWidth*2, windowHeight*2); // Provide the framebuffer sizes, on retina its 2x in x and y
    
//    camera* secondCam = new camera();
//    renderer* secondView = new renderer(window,&scene,secondCam);
//    secondView->setViewport(windowWidth, windowHeight, windowWidth, windowHeight);
//
//    camera* thirdCam = new camera();
//    renderer* thirdView = new renderer(window,&scene,thirdCam);
//    thirdView->setViewport(0, 0, windowWidth, windowHeight);
//
//    camera* fourthCam = new camera();
//    renderer* fourthView = new renderer(window,&scene,fourthCam);
//    fourthView->setViewport(windowWidth, 0, windowWidth, windowHeight);
    
    
    
    myController = new keyboardAndMouse(window,&scene,myView); // Initialise the controller, is provided reference to the model and the view so it can access both
    
    
    
    bool running = true;
    do {                                        // run until the window is closed
        double currentTime = glfwGetTime();     // retrieve timelapse
        
        // Game loop - Input
        glfwPollEvents();                       // from the GLFW documentation - Processes only those events that have already been received and then returns immediately.
        
        // Game loop - Update
        scene.update(currentTime);              // update (physics, animation, structures, etc)
        
        // Game loop - Render
        myView->render();
//        secondView->render();
//        thirdView->render();
//        fourthView->render();
        
        // Swap buffers done here so that multiple viewports can be rendered before they are put on screen
        glfwSwapBuffers(window);                // swap buffers (avoid flickering and tearing)

        running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);    // exit if escape key pressed
        running &= (glfwWindowShouldClose(window) != GL_TRUE);
    } while (running);
    
    // Make sure to remove any items from the heap, get rid of dangling pointers
    delete myController;
    myController = NULL;
    delete myView;
    myView = NULL;
    delete mainCamera;
    mainCamera = NULL;
    
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
    
//    debugGL();
    
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On windows machine course uses version 4.5 on mac i need to use 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );
    
    // Following two lines are required for running on mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


// callback functions call the methods of the controller or renderer, so that functionality can be swapped as need be by changing the object
void onResizeCallback(GLFWwindow* window, int w, int h) {
    windowWidth = w;
    windowHeight = h;
    
    // Call methods of the renderers used
    myView->setWindowDimensions(w, h);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    myController->onKey(window, key, scancode, action, mods);
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    myController->onMouseButton(window, button, action, mods);
}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
    myController->onMouseMove(window, x, y ); // So we can swap out the controller and will have no effect on the callback
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
//    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)openGLDebugCallback, nullptr); // debugGL does not work, currently throws Thread #: EXC bad access error
    
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


