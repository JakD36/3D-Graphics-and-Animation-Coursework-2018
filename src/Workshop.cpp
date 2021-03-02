//
// Created by Jack Davidson on 08/08/2020.
//

#include "Workshop.h"
#include "Core/OpenGL/GlWindow.h"
#include "Core/WindowEvent.h"
#include "Core/Input/Input.h"
#include <cstdio>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "Scenes/Scene1.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/Shaders/ShaderManager.h"

#include "Profiling/ProfilerService.h"
#include "Utils/DebugUtils.h"
#include "GameObject/GameObject.hpp"
#include "Rendering/ImGui/ShaderEditorWindow.h"
#include "Rendering/Material/MaterialResource.h"
#include "Profiling/ProfilerWindow.h"
#include "Profiling/MemoryProfiler.h"
#include "Rendering/ImGui/ImGuiStyle.h"

#include <memory>

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

    Scene1 scene;
    auto view = std::make_unique<Renderer>(m_window.get());

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize((GLFWwindow*)m_window->GetNativeWindow(), &framebufferWidth, &framebufferHeight);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    SetImGuiStyle();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_window->GetNativeWindow(), true);
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


        if(Input::GetKeyDown(KEY_SPACE))
        {
            static bool enabled = true;
            enabled = !enabled;
            m_window->SetVSync(enabled);
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
        view->Render(m_window.get(),&scene);

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