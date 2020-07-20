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
#include "../Include/DearImgui/imgui_impl_opengl3.h"
#include "../Include/DearImgui/imgui_impl_glfw.h"

#include "Profiling/ProfilerService.h"
#include "Profiling/ProfileTag.h"
#include <gsl/pointers>
#include "Utils/DebugUtils.h"
#include "GameObject/GameObject.hpp"

#include "Utils/ShaderEditor.h"
#include "Material/MaterialResource.h"
#include "Profiling/MemoryProfiler.h"
#include "Profiling/ProfilerWindow.h"

using namespace std;
using gsl::owner;

void ShaderTool(vector<GameObject>& objs);

unique_ptr<Renderer> s_view; // is global to be accessible through callbacks
unique_ptr<Controller> s_controller; // s_controller is global to be accessible through the callbacks

void SetStyle();

int main(int argc, char *argv[])
{
    DEBUGLOG(("Help me %s\n","dog"));

    int windowHeight = 580; // height of the window
    int windowWidth = (int)(windowHeight * 16.0f/9.0f); // width of the window

    owner<GLFWwindow*> p_window = InitOpenGL(windowWidth, windowHeight); // Initialise OpenGL window,

    // Using a Model view controller pattern, allows for the addition of new controllers, scenes or even a change in the Renderer
    Scene1 scene;

    s_view = make_unique<Renderer>(p_window); // Initialise our rendering object, with the scene it will render and the camera it will be using

    // Was Looking into creating multiple views, using multiple Renderer objects, this is easily achieved
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(p_window, &framebufferWidth, &framebufferHeight);

    s_view->SetViewport(framebufferWidth * 0.25f, framebufferHeight * 0.25f, framebufferWidth* 0.5f, framebufferHeight* 0.5f); // Provide the framebuffer sizes, on retina its 2x in x and y

    s_controller = make_unique<KeyboardAndMouse>(p_window, &scene); // Initialise the controller, is provided reference to the model and the view so it can access both
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    SetStyle();
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

        // bool show_demo_window = true;
        // ImGui::ShowDemoWindow(&show_demo_window);

        glfwPollEvents(); // From the GLFW documentation - Processes only those events that have already been received and then returns immediately.
        scene.Update(deltaTime);
        ShaderEditorWindow();
        s_view->Render(&scene);


        { // Render ImGui
            DrawProfiler();
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

void SetStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
    colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
    colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

    style->ChildRounding = 4.0f;
    style->FrameBorderSize = 1.0f;
    style->FrameRounding = 2.0f;
    style->GrabMinSize = 7.0f;
    style->PopupRounding = 2.0f;
    style->ScrollbarRounding = 12.0f;
    style->ScrollbarSize = 13.0f;
    style->TabBorderSize = 1.0f;
    style->TabRounding = 0.0f;
    style->WindowRounding = 4.0f;

}