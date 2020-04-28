// Standard libraries
#include <string>
#include <cstdio>

#if(WIN32)
#define GLEW_STATIC
#endif

// OpenGL - glew, glfw and glm
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

#include "Utils/ProfilerService.h"
#include "Utils/ProfileTag.h"
#include <gsl/pointers>
#include "Utils/DebugUtils.h"

using namespace std;
using gsl::owner;

unique_ptr<Renderer> s_view; // is global to be accessible through callbacks
unique_ptr<Controller> s_controller; // s_controller is global to be accessible through the callbacks

int main(int argc, char *argv[])
{
    DEBUGLOG(("Help me %s\n","dog"));

    int windowHeight = 320; // height of the window
    int windowWidth = (int)(windowHeight * 16.0f/9.0f); // width of the window


    owner<GLFWwindow*> p_window = InitOpenGL(windowWidth, windowHeight); // Initialise OpenGL window,

    // Using a Model view controller pattern, allows for the addition of new controllers, scenes or even a change in the Renderer
    Scene1 scene;

    s_view = make_unique<Renderer>(p_window); // Initialise our rendering object, with the scene it will render and the camera it will be using

    // Was Looking into creating multiple views, using multiple Renderer objects, this is easily achieved
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(p_window, &framebufferWidth, &framebufferHeight);
    s_view->SetViewport(0, 0, framebufferWidth, framebufferHeight); // Provide the framebuffer sizes, on retina its 2x in x and y

    s_controller = make_unique<KeyboardAndMouse>(p_window, &scene); // Initialise the controller, is provided reference to the model and the view so it can access both
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(p_window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    ShaderManager* smInstance = ShaderManager::GetInstance();
    double prevTime = glfwGetTime();
    while (glfwWindowShouldClose(p_window) != GL_TRUE){ // run until the window is closed
        PROFILE(gameLoopProfile,"mainloop");

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - prevTime;
        prevTime = currentTime;

        smInstance->Update();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // bool show_demo_window = true;
        // ImGui::ShowDemoWindow(&show_demo_window);

        glfwPollEvents(); // From the GLFW documentation - Processes only those events that have already been received and then returns immediately.
        scene.Update(deltaTime);
        s_view->Render(&scene);

        { // Render ImGui
            ProfilerService::GetInstance()->Draw();
            PROFILE(debugRenderProfile,"Imgui Draw");
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            ENDPROFILE(debugRenderProfile);
        }
       
        { // Perform Swap Buffer
            PROFILE(swapBufferProfile,"Swap Buffer");
            glfwSwapBuffers(p_window); // swap buffers (avoid flickering and tearing)
            ENDPROFILE(swapBufferProfile);
        }

        ENDPROFILE(gameLoopProfile);
    }

    EndProgram(p_window);
    return 0;
}
