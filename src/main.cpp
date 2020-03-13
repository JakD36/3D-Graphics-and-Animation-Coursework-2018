// Standard libraries
#include <string>
#include <cstdio>

#if(WIN32)
#define GLEW_STATIC
#endif

// OpenGL - GLEW, GLFW and GLM
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// My classes
#include "OpenGLSetup.h"
#include "Scenes/Scene1.hpp"
#include "Controllers/Controller.hpp"
#include "Controllers/KeyboardAndMouse.hpp"
#include "Views/Renderer.hpp"
#include "Shaders/ShaderManager.h"

#include "../Include/DearImgui/imgui.h"
#include "../Include/DearImgui/imgui_impl_glfw.h"
#include "../Include/DearImgui/imgui_impl_opengl3.h"

#include "Utils/ProfileService.h"

using namespace std;

// Global variables
GLFWwindow*             window;                     // Window the app will be displayed in
int                     windowWidth = (int)(240.0f*16.0f/9.0f); // width of the window
int                     windowHeight = 240;         // height of the window

Renderer* myView; // is global to be accessible through callbacks
Controller* myController; // myController is global to be accessible through the callbacks

int main(int argc, char *argv[])
{
    ProfilerService* profilerInstance = ProfilerService::GetInstance();
    int profiler = profilerInstance->StartTimer("main");

    InitOpenGL(); // Initialise OpenGL window,

    // Using a Model view controller pattern, allows for the addition of new controllers, scenes or even a change in the Renderer
    Scene1 scene; // Initialise the scene i.e the model

    myView = new Renderer(window); // Initialise our rendering object, with the scene it will render and the camera it will be using

    // Was Looking into creating multiple views, using multiple Renderer objects, this is easily achieved
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    myView->SetViewport(0, 0, framebufferWidth, framebufferHeight); // Provide the framebuffer sizes, on retina its 2x in x and y
    
    myController = new KeyboardAndMouse(window,&scene); // Initialise the controller, is provided reference to the model and the view so it can access both
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    ShaderManager* smInstance = ShaderManager::GetInstance();

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

//        ImGui::Begin("Debug",NULL);
//        string debug = to_string(myView->GetCamera()->GetForward().x) + ", " + to_string(myView->GetCamera()->GetForward().y) + ", " + to_string(myView->GetCamera()->GetForward().z);
//        ImGui::Text(debug.c_str());
//        ImGui::End();

        myView->Render(&scene);

        { // Render ImGui
            profilerInstance->Draw();
            int profiler2 = ProfilerService::GetInstance()->StartTimer("Imgui Draw");
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            profilerInstance->StopTimer(profiler2);
        }
       
        { // Perform Swap Buffer
            int profiler3 = profilerInstance->StartTimer("Swap Buffer");
            glfwSwapBuffers(window);                // swap buffers (avoid flickering and tearing)
            profilerInstance->StopTimer(profiler3);
        }

        profilerInstance->StopTimer(profiler);
    } while (glfwWindowShouldClose(window) != GL_TRUE);
    
    // Make sure to remove any items from the heap, get rid of dangling pointers
    delete myController;
    myController = NULL;
    delete myView;
    myView = NULL;

    profilerInstance->StopTimer(profiler);
    return 0;
}
