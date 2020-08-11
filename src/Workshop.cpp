//
// Created by Jack Davidson on 08/08/2020.
//

#include "Workshop.h"
#include "Core/OpenGL/GlWindow.h"
#include "Core/WindowEvent.h"
#include "Core/Input/Input.h"
#include <cstdio>

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

    // Renderer
    // Scene
    // ImGui
    // ResourceSystem
    while(m_running)
    {
        float dt = m_window->GetDeltaTime();
        // ResourceSystem->Update();

        // GUI->Update();

        // Render

        // Update Systems
        Input::Update();
        m_window->Update();
    }
}