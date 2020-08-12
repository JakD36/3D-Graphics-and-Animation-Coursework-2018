//
// Created by Jack Davidson on 08/08/2020.
//

#include "Workshop.h"
#include "Core/OpenGL/GlWindow.h"
#include "Core/WindowEvent.h"
#include "Core/Input/Input.h"
#include <cstdio>

#include "../Include/DearImgui/imgui.h"
#include "../Include/DearImgui/imgui_impl_opengl3.h"
#include "../Include/DearImgui/imgui_impl_glfw.h"

#include "Scenes/Scene1.hpp"
#include "Controllers/Controller.hpp"
#include "Controllers/KeyboardAndMouse.hpp"
#include "Rendering/Views/Renderer.hpp"
#include "Rendering/Shaders/ShaderManager.h"

#include "Profiling/ProfilerService.h"
#include "Utils/DebugUtils.h"
#include "GameObject/GameObject.hpp"
#include "Rendering/ImGui/ShaderEditorWindow.h"
#include "Rendering/Material/MaterialResource.h"
#include "Profiling/ProfilerWindow.h"
#include "Profiling/MemoryProfiler.h"

#include <memory>

void SetImGuiStyle();

Application* CreateApplication() noexcept
{
    return new Workshop();
}

Workshop::Workshop() {
    m_window = std::make_unique<GlWindow>("Workshop",800,450);
    m_window->RegisterEventListener([this] (WindowEvent& event){ this->OnEvent(event); });
}

Workshop::~Workshop() {}

void Workshop::OnEvent(WindowEvent &event) {
    if((event.GetType() & WindowEventType::WINDOW_CLOSE) > 0)
    {
        m_running = false;
        return;
    }

    if( (event.GetType() & (WindowEventType::KEY_EVENTS | WindowEventType::MOUSE_EVENTS)) > 0)
    {
        Input::OnEvent(event);
        return;
    }

    if((event.GetType() & WindowEventType::RENDERER_EVENTS) > 0)
    {
        printf("Send to renderer\n");
        return;
    };
}

void Workshop::Run() {
    // Initialise

    GLFWwindow* window = (GLFWwindow*)m_window->GetNativeWindow();

    Scene1 scene;
    auto view = std::make_unique<Renderer>(window);

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    view->SetViewport(framebufferWidth * 0.25f, framebufferHeight * 0.25f, framebufferWidth * 0.5f, framebufferHeight* 0.5f); // Provide the framebuffer sizes, on retina its 2x in x and y

    auto controller = std::make_unique<KeyboardAndMouse>(window, &scene); // Initialise the controller, is provided reference to the model and the view so it can access both

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    SetImGuiStyle();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");

    ShaderManager* smInstance = ShaderManager::GetInstance();
    ResourceManager<MeshResource> *meshManager = ResourceManager<MeshResource>::GetInstance();
    ResourceManager<TextureResource> *textureManager = ResourceManager<TextureResource>::GetInstance();
    ResourceManager<MaterialResource> *materialManager = ResourceManager<MaterialResource>::GetInstance();
    ResourceManager<RenderTaskResource> *renderTaskManager = ResourceManager<RenderTaskResource>::GetInstance();

    // Renderer
    // Scene
    // ImGui
    // ResourceSystem
    while(m_running)
    {
        PROFILE(gameLoopProfile,"mainloop");

        float dt = m_window->GetDeltaTime();

        if(Input::GetKeyDown(KEY_ESCAPE))
        {
            static bool enabled = true;
            enabled = !enabled;
            m_window->SetCursor(enabled);
        }

        smInstance->Update();
        meshManager->UpdateModified();
        textureManager->UpdateModified();
        materialManager->UpdateModified();
        renderTaskManager->UpdateModified();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        scene.Update(dt);
        ShaderEditorWindow();
        view->Render(&scene);

        { // Render ImGui
            DrawProfilerWindow();
            PROFILE(debugRenderProfile,"Imgui Draw");
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            ENDPROFILE(debugRenderProfile);
        }

        // Update Systems
        Input::Update();
        { // Perform Swap Buffer
            PROFILE(swapBufferProfile,"Swap Buffer");
            m_window->Update();
            ENDPROFILE(swapBufferProfile);
        }

        ENDPROFILE(gameLoopProfile);
        MemoryProfiler::GetInstance()->NextFrame();
    }
}

void SetImGuiStyle()
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