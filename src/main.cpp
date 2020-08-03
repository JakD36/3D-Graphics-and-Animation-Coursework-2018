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
#include "OpenGL/OpenGLSetup.h"
#include "Scenes/Scene1.hpp"
#include "Controllers/Controller.hpp"
#include "Controllers/KeyboardAndMouse.hpp"
#include "Rendering/Views/Renderer.hpp"
#include "Rendering/Shaders/ShaderManager.h"

#include "../Include/DearImgui/imgui.h"
#include "../Include/DearImgui/imgui_impl_opengl3.h"
#include "../Include/DearImgui/imgui_impl_glfw.h"

#include "Profiling/ProfilerService.h"
#include <gsl/pointers>
#include "Utils/DebugUtils.h"
#include "GameObject/GameObject.hpp"

#include "Rendering/ImGui/ShaderEditorWindow.h"
#include "Rendering/Material/MaterialResource.h"
#include "Profiling/MemoryProfiler.h"
#include "Profiling/ProfilerWindow.h"

using namespace std;
using gsl::owner;

unique_ptr<Renderer> s_view; // is global to be accessible through callbacks
unique_ptr<Controller> s_controller; // s_controller is global to be accessible through the callbacks

int main(int argc, char *argv[])
{
    DEBUGLOG(("Help me %s\n","dog"));

    int windowHeight = 580;
    int windowWidth = (int)(windowHeight * 16.0f/9.0f);

    owner<GLFWwindow*> p_window = InitOpenGL(windowWidth, windowHeight);

    Scene1 scene;

    s_view = make_unique<Renderer>(p_window);

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(p_window, &framebufferWidth, &framebufferHeight);

    s_view->SetViewport(framebufferWidth * 0.25f, framebufferHeight * 0.25f, framebufferWidth* 0.5f, framebufferHeight* 0.5f); // Provide the framebuffer sizes, on retina its 2x in x and y

    s_controller = make_unique<KeyboardAndMouse>(p_window, &scene); // Initialise the controller, is provided reference to the model and the view so it can access both
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    SetImGuiStyle();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(p_window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    ShaderManager* smInstance = ShaderManager::GetInstance();
    ResourceManager<MeshResource> *meshManager = ResourceManager<MeshResource>::GetInstance();
    ResourceManager<TextureResource> *textureManager = ResourceManager<TextureResource>::GetInstance();
    ResourceManager<MaterialResource> *materialManager = ResourceManager<MaterialResource>::GetInstance();
    ResourceManager<RenderTaskResource> *renderTaskManager = ResourceManager<RenderTaskResource>::GetInstance();

    double prevTime = glfwGetTime();
    while (glfwWindowShouldClose(p_window) != GL_TRUE){ // run until the window is closed
        PROFILE(gameLoopProfile,"mainloop");

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - prevTime;
        prevTime = currentTime;

        smInstance->Update();
        meshManager->UpdateModified();
        textureManager->UpdateModified();
        materialManager->UpdateModified();
        renderTaskManager->UpdateModified();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glfwPollEvents(); // From the GLFW documentation - Processes only those events that have already been received and then returns immediately.
        scene.Update(deltaTime);
        ShaderEditorWindow();
        s_view->Render(&scene);

        { // Render ImGui
            DrawProfilerWindow();
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
        MemoryProfiler::GetInstance()->NextFrame();
    }

    EndProgram(p_window);
    return 0;
}

