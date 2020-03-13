//
// Created by Jack Davidson on 13/03/2020.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenGLSetup.h"
#include "OpenGLCallbacks.h"
#include "Utils/ProfileService.h"
#include <string>

using namespace std;

void InitOpenGL(){
    ProfilerService* profilerService = ProfilerService::GetInstance();
    int profiler = profilerService->StartTimer("Init OpenGL");

    if (!glfwInit()) {                                  // Checking for GLFW
        printf("Could not initialise GLFW...\n");
    }
    glfwSetErrorCallback(ErrorCallbackGLFW);            // Setup a function to catch and display all GLFW errors.

    HintsGLFW();                                        // Setup glfw with various hints.

    // Start a window using GLFW
    string title = "My OpenGL Application";
    window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
    if (!window) {                                      // Window or OpenGL context creation failed
        printf("Could not initialise GLFW...\n");
        EndProgram();
    }

    glfwMakeContextCurrent(window);                     // making the OpenGL context current

    // Start GLEW (note: always initialise GLEW after creating your window context.)
    glewExperimental = GL_TRUE;                         // hack: catching them all - forcing newest debug callback (glDebugMessageCallback)
    GLenum errGLEW = glewInit();
    if (GLEW_OK != errGLEW) {                           // Problems starting GLEW?
        printf("Could not initialise GLEW...\n");
        EndProgram();
    }

    SetupOpenglDebug();

    // Setup all the message loop callbacks.
    glfwSetWindowSizeCallback(window, OnResizeCallback);            // Set callback for resize
    glfwSetKeyCallback(window, OnKeyCallback);                      // Set Callback for keys
    glfwSetMouseButtonCallback(window, OnMouseButtonCallback);      // Set callback for mouse click
    glfwSetCursorPosCallback(window, OnMouseMoveCallback);          // Set callback for mouse move
    glfwSetScrollCallback(window, OnMouseWheelCallback);            // Set callback for mouse wheel.

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);    // Set mouse cursor.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // Remove curser for FPS cam

    glfwSwapInterval(1);    // Ony render when synced (V SYNC each 1 frame)
    glfwWindowHint(GLFW_SAMPLES, 32);
    glfwWindowHint(GLFW_STEREO, GL_FALSE);

    profilerService->StopTimer(profiler);
}

void EndProgram() {
    ProfilerService* profilerService = ProfilerService::GetInstance();
    int profiler = profilerService->StartTimer("End glfw");

    glfwMakeContextCurrent(window);             // destroys window handler
    glfwTerminate();                            // destroys all windows and releases resources.

    profilerService->StopTimer(profiler);
}

void HintsGLFW() {
    ProfilerService* profilerService = ProfilerService::GetInstance();
    int profiler = profilerService->StartTimer("HintsGLFW");

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);            // Create context in debug mode - for debug message callback
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On windows machine course uses version 4.5 on mac i need to use 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );

    // Following two lines are required for running on mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    profilerService->StopTimer(profiler);
}

void SetupOpenglDebug() {
    ProfilerService* profilerService = ProfilerService::GetInstance();
    int profiler = profilerService->StartTimer("Debug GL");

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
    profilerService->StopTimer(profiler);
}
