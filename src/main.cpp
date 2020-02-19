// Standard libraries
#include <string>
#include <stdio.h>

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
#include "Shaders/ShaderManager.h"
#include "Utils/ProfileService.h"

#include "../Include/DearImgui/imgui.h"
#include "../Include/DearImgui/imgui_impl_glfw.h"
#include "../Include/DearImgui/imgui_impl_opengl3.h"

using namespace std;

// Our prototypes for OpenGL functions used throughout the program, mainly the callbacks to handle user input
void ErrorCallbackGLFW(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void OnResizeCallback(GLFWwindow* window, int w, int h);
void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void OnMouseMoveCallback(GLFWwindow* window, double x, double y);
void OnMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
void DebugGL();
static void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);

// Prototypes for setting up OpenGL and closing it down
void InitOpenGL();
void HintsGLFW();
void EndProgram();

// Global variables
GLFWwindow*             window;                     // Window the app will be displayed in
int                     windowWidth = (int)(480.0f*16.0f/9.0f); // width of the window
int                     windowHeight = 480;         // height of the window

Controller* myController; // myController is global to be accessible through the callbacks
Renderer* myView; // is global to be accessible through callbacks

ShaderManager* ShaderManager::m_instance = NULL;
ProfilerService* ProfilerService::m_instance = NULL;

int main(int argc, char *argv[])
{
    ProfilerService* profilerInstance = ProfilerService::GetInstance();
    int profiler = profilerInstance->StartTimer("main");

    InitOpenGL(); // Initialise OpenGL window,
    
    // Using a Model view controller pattern, allows for the addition of new controllers, scenes or even a change in the Renderer
    Scene1 scene; // Initialise the scene i.e the model
    
    Camera* mainCamera = new Camera(); // Initialise the main camera, FPS camera attached to player!

    myView = new Renderer(window,&scene,mainCamera); // Initialise our rendering object, with the scene it will render and the camera it will be using

    // Was Looking into creating multiple views, using multiple Renderer objects, this is easily achieved
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    myView->SetViewport(0, 0, framebufferWidth, framebufferHeight); // Provide the framebuffer sizes, on retina its 2x in x and y
    
    myController = new KeyboardAndMouse(window,&scene,myView); // Initialise the controller, is provided reference to the model and the view so it can access both
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    ShaderManager* smInstance = ShaderManager::GetInstance();

    bool running = true;
    do { // run until the window is closed
        int profiler = profilerInstance->StartTimer("mainloop");
        double currentTime = glfwGetTime();

        smInstance->Update();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // bool show_demo_window = true;
        // ImGui::ShowDemoWindow(&show_demo_window);

        glfwPollEvents(); // From the GLFW documentation - Processes only those events that have already been received and then returns immediately.

        scene.Update(currentTime);              // update (physics, animation, structures, etc)

        myView->Render();

        { // Render ImGui
            profilerInstance->Draw();
            int profiler2 = ProfilerService::GetInstance()->StartTimer("Imgui Draw");
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            profilerInstance->StopTimer(profiler2);
        }
       
        { // Perform Swap Buffer
            int profiler3 = profilerInstance->StartTimer("Swap Buffer");
            // Swap buffers done here so that multiple viewports can be rendered before they are put on screen
            glfwSwapBuffers(window);                // swap buffers (avoid flickering and tearing)
            profilerInstance->StopTimer(profiler3);
        }
        running &= (glfwWindowShouldClose(window) != GL_TRUE);

        profilerInstance->StopTimer(profiler);
    } while (running);
    
    // Make sure to remove any items from the heap, get rid of dangling pointers
    delete myController;
    myController = NULL;
    delete myView;
    myView = NULL;
    delete mainCamera;
    mainCamera = NULL;

    profilerInstance->StopTimer(profiler);
    return 0;
}


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
    
    //DebugGL();
    
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

// callback functions call the methods of the controller or Renderer, so that functionality can be swapped as need be by changing the object
void OnResizeCallback(GLFWwindow* window, int w, int h) {
    ProfilerService* profilerService = ProfilerService::GetInstance();
    int profiler = profilerService->StartTimer("On resize callback");
    
    windowWidth = w;
    windowHeight = h;
    
    // Call methods of the renderers used
    myView->SetWindowDimensions(w, h);

    profilerService->StopTimer(profiler);
}

void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    myController->OnKey(window, key, scancode, action, mods);
}

void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    myController->OnMouseButton(window, button, action, mods);
}

void OnMouseMoveCallback(GLFWwindow* window, double x, double y) {
    myController->OnMouseMove(window, x, y ); // So we can swap out the controller and will have no effect on the callback
}

void OnMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Taken from F21GA 3D Graphics and Animation Labs

void DebugGL() {
    ProfilerService* profilerService = ProfilerService::GetInstance();
    int profiler = profilerService->StartTimer("Debug GL");
    
    //Output some debugging information
    printf("VENDOR %s\n",(char *)glGetString(GL_VENDOR));
    printf("VERSION %s\n",(char *)glGetString(GL_VERSION));
    printf("RENDERER %s\n",(char *)glGetString(GL_RENDERER));

    // Enable Opengl Debug
    // glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)OpenGLDebugCallback, nullptr); // debugGL does not work, currently throws Thread #: EXC bad access error
    
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);

    profilerService->StopTimer(profiler);
}

static void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam)
{
    
    printf("---------------------opengl-callback------------\n");
    printf("Message: %s",message);
    printf("type: ");
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            printf("ERROR");
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            printf("DEPRECATED_BEHAVIOR");
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            printf("UNDEFINED_BEHAVIOR");
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            printf("PORTABILITY");
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            printf("PERFORMANCE");
            break;
        case GL_DEBUG_TYPE_OTHER:
            printf("OTHER");
            break;
    }
    printf(" --- ");
    
    printf("id: %d --- ",id);
    printf("severity: ");
    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            printf("LOW");
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            printf("MEDIUM");
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            printf("HIGH");
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            printf("NOTIFICATION");
    }
    printf("\n");
    printf("-----------------------------------------\n");
}

void ErrorCallbackGLFW(int error, const char* description) {
    printf("Error GLFW: %s\n",description);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


