//
// Created by Jack Davidson on 13/03/2020.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenGLSetup.h"
#include "OpenGLCallbacks.h"
#include "Profiling/ProfilerService.h"

using namespace std;

GLFWwindow* InitOpenGL(int windowWidth, int windowHeight){
    PROFILE(p,"Init OpenGL");

    if (!glfwInit()) {                                  // Checking for GLFW
        printf("Could not initialise GLFW...\n");
    }
    glfwSetErrorCallback(ErrorCallbackGLFW);            // Setup a function to catch and display all GLFW errors.

    HintsGLFW();                                        // Setup glfw with various hints.

    // Start a window using GLFW
    string title = "My OpenGL Application";
    GLFWwindow* p_window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
    if (!p_window) {                                      // Window or OpenGL context creation failed
        printf("Could not initialise GLFW...\n");
        EndProgram(p_window);
    }

    glfwMakeContextCurrent(p_window);                     // making the OpenGL context current

    // Start GLEW (note: always initialise GLEW after creating your window context.)
    glewExperimental = GL_TRUE; // hack: catching them all - forcing newest debug callback (glDebugMessageCallback)
    GLenum errGLEW = glewInit();
    if (GLEW_OK != errGLEW) { // Problems starting GLEW?
        printf("Could not initialise GLEW...\n");
        EndProgram(p_window);
    }

    SetupOpenglDebug();

    // Setup all the message loop callbacks.
    glfwSetWindowSizeCallback(p_window, OnResizeCallback);            // Set callback for resize
    glfwSetKeyCallback(p_window, OnKeyCallback);                      // Set Callback for keys
    glfwSetMouseButtonCallback(p_window, OnMouseButtonCallback);      // Set callback for mouse click
    glfwSetCursorPosCallback(p_window, OnMouseMoveCallback);          // Set callback for mouse move
    glfwSetScrollCallback(p_window, OnMouseWheelCallback);            // Set callback for mouse wheel.

    glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // Remove curser for FPS cam

    glfwSwapInterval(1);    // Ony render when synced (V SYNC each 1 frame)
    glfwWindowHint(GLFW_SAMPLES, 32);
    glfwWindowHint(GLFW_STEREO, GL_FALSE);

    ENDPROFILE(p);
    return p_window;
}

void EndProgram(GLFWwindow* p_window) {
    glfwMakeContextCurrent(p_window); // destroys window handler
    glfwTerminate(); // destroys all windows and releases resources.
}

void HintsGLFW() {
    PROFILE(p,"HintsGLFW");

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // Create context in debug mode - for debug message callback
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On windows machine course uses version 4.5 on mac i need to use 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );

    // Following two lines are required for running on mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ENDPROFILE(p);
}

void SetupOpenglDebug() {
    PROFILE(p,"Debug GL");

    //Output some debugging information
    printf("VENDOR %s\n",(char *)glGetString(GL_VENDOR));
    printf("VERSION %s\n",(char *)glGetString(GL_VERSION));
    printf("RENDERER %s\n",(char *)glGetString(GL_RENDERER));

    // Enable Opengl Debug
    if(glDebugMessageCallback)
    {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
    }
    else
    {
        printf("OpenGL Debug Output not available\n");
    }
    ENDPROFILE(p);
}
