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
#include "Scenes/SceneGraph.hpp"
#include "Scenes/Scene1.hpp"
#include "Controllers/Controller.hpp"
#include "Controllers/KeyboardAndMouse.hpp"
#include "Views/Renderer.hpp"
#include "Utils/ProfileService.h"

#include "../Include/DearImgui/imgui.h"
#include "../Include/DearImgui/imgui_impl_glfw.h"
#include "../Include/DearImgui/imgui_impl_opengl3.h"


using namespace std;

// initialise Static variables
ShaderLoader* ShaderLoader::m_instance = NULL;
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
int                     windowWidth = (int)(720.0f*16.0f/9.0f); // width of the window
int                     windowHeight = 720;         // height of the window

Controller* myController; // myController is global to be accessible through the callbacks
Renderer* myView; // is global to be accessible through callbacks

ProfilerService* ProfilerService::m_instance = NULL;

int main(int argc, char *argv[])
{
    int profiler = ProfilerService::GetInstance()->StartTimer("main");
    // string path = argv[0];
    // cout<<getenv("PWD")<<endl;

    // Intialise the program and the scene
    initOpenGL(); // Initialise OpenGL window,
    
    // Using a Model view controller pattern, allows for the addition of new controllers, scenes or even a change in the Renderer
    Scene1 scene; // Initialise the scene i.e the model
    
    Camera* mainCamera = new Camera(); // Initialise the main camera, FPS camera attached to player!
    
    myView = new Renderer(window,&scene,mainCamera); // Initialise our rendering object, with the scene it will render and the camera it will be using
    
    /*
     Was Looking into creating multiple views, using multiple Renderer objects, this is easily achieved
    */
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    myView->SetViewport(0, 0, framebufferWidth, framebufferHeight); // Provide the framebuffer sizes, on retina its 2x in x and y
    
//    camera* secondCam = new camera();
//    Renderer* secondView = new Renderer(window,&scene,secondCam);
//    secondView->SetViewport(windowWidth, windowHeight, windowWidth, windowHeight);
//
//    camera* thirdCam = new camera();
//    Renderer* thirdView = new Renderer(window,&scene,thirdCam);
//    thirdView->SetViewport(0, 0, windowWidth, windowHeight);
//
//    camera* fourthCam = new camera();
//    Renderer* fourthView = new Renderer(window,&scene,fourthCam);
//    fourthView->SetViewport(windowWidth, 0, windowWidth, windowHeight);
    
    myController = new KeyboardAndMouse(window,&scene,myView); // Initialise the controller, is provided reference to the model and the view so it can access both
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    bool running = true;
    do { // run until the window is closed
        int profiler = ProfilerService::GetInstance()->StartTimer("mainloop");
        double currentTime = glfwGetTime();     // retrieve timelapse
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);

        {
            int profiler = ProfilerService::GetInstance()->StartTimer("Imgui Window");
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            // ImGui::Text("Profiler %s %i",profiler.GetIdentifier().c_str(),10);//InstrumentedProfiler::s_timings.length);               // Display some text (you can use a format strings too)
            // ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            // ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();

            ProfilerService::GetInstance()->StopTimer(profiler);
        }

        // Game loop - Input
        glfwPollEvents();                       // from the GLFW documentation - Processes only those events that have already been received and then returns immediately.
        
        // Game loop - Update
        scene.Update(currentTime);              // update (physics, animation, structures, etc)
        
        // Game loop - Render
        myView->Render();
//        secondView->Render();
//        thirdView->Render();
//        fourthView->Render();
        ProfilerService* instance = ProfilerService::GetInstance();
        instance->Draw();
        int profiler2 = ProfilerService::GetInstance()->StartTimer("Imgui Draw");
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ProfilerService::GetInstance()->StopTimer(profiler2);
        
        int profiler3 = ProfilerService::GetInstance()->StartTimer("Swap Buffer");
        // Swap buffers done here so that multiple viewports can be rendered before they are put on screen
        glfwSwapBuffers(window);                // swap buffers (avoid flickering and tearing)
        ProfilerService::GetInstance()->StopTimer(profiler3);
        //running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);    // exit if escape key pressed
        running &= (glfwWindowShouldClose(window) != GL_TRUE);
        
        ProfilerService::GetInstance()->StopTimer(profiler);
    } while (running);
    
    // Make sure to remove any items from the heap, get rid of dangling pointers
    delete myController;
    myController = NULL;
    delete myView;
    myView = NULL;
    delete mainCamera;
    mainCamera = NULL;
    
    ProfilerService::GetInstance()->StopTimer(profiler);
    return 0;
}



void initOpenGL(){
    int profiler = ProfilerService::GetInstance()->StartTimer("Init OpenGL");
    
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
    
    ProfilerService::GetInstance()->StopTimer(profiler);
}

void endProgram() {
    int profiler = ProfilerService::GetInstance()->StartTimer("End glfw");
    
    glfwMakeContextCurrent(window);             // destroys window handler
    glfwTerminate();                            // destroys all windows and releases resources.
    
    ProfilerService::GetInstance()->StopTimer(profiler);
}

void hintsGLFW() {
    int profiler = ProfilerService::GetInstance()->StartTimer("hintsGLFW");
    
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);            // Create context in debug mode - for debug message callback
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On windows machine course uses version 4.5 on mac i need to use 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );
    
    // Following two lines are required for running on mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    ProfilerService::GetInstance()->StopTimer(profiler);
}


// callback functions call the methods of the controller or Renderer, so that functionality can be swapped as need be by changing the object
void onResizeCallback(GLFWwindow* window, int w, int h) {
    int profiler = ProfilerService::GetInstance()->StartTimer("On resize callback");
    
    windowWidth = w;
    windowHeight = h;
    
    // Call methods of the renderers used
    myView->SetWindowDimensions(w, h);

    ProfilerService::GetInstance()->StopTimer(profiler);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    myController->OnKey(window, key, scancode, action, mods);
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    myController->OnMouseButton(window, button, action, mods);
}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
    myController->OnMouseMove(window, x, y ); // So we can swap out the controller and will have no effect on the callback
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Taken from F21GA 3D Graphics and Animation Labs

void debugGL() {
    int profiler = ProfilerService::GetInstance()->StartTimer("Debug GL");
    
    //Output some debugging information
    cout << "VENDOR: " << (char *)glGetString(GL_VENDOR) << endl;
    cout << "VERSION: " << (char *)glGetString(GL_VERSION) << endl;
    cout << "RENDERER: " << (char *)glGetString(GL_RENDERER) << endl;
    
    // Enable Opengl Debug
//    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)openGLDebugCallback, nullptr); // debugGL does not work, currently throws Thread #: EXC bad access error
    
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);

    ProfilerService::GetInstance()->StopTimer(profiler);
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


