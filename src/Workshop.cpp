//
// Created by Jack Davidson on 08/08/2020.
//

#include "Workshop.h"
#include "Core/OpenGL/GlWindow.h"
#include "Core/WindowEvent.h"
#include <cstdio>

Application* CreateApplication() noexcept
{
    return new Workshop();
}

Workshop::Workshop() {
    m_window = std::make_unique<GlWindow>("Workshop",1031,580);
    m_window->RegisterEventListener([this] (WindowEvent& event){ this->OnEvent(event); });
}

Workshop::~Workshop() {}

void Workshop::OnEvent(WindowEvent &event) {
    if(((unsigned long)event.GetType() & (unsigned long)WindowEventType::WINDOW_CLOSE) > 0)
    {
        m_running = false;
        return;
    }

    if(((unsigned long)event.GetType() & ((unsigned long)WindowEventType::KEY_EVENTS | (unsigned long)WindowEventType::MOUSE_EVENTS)) > 0)
    {
        printf("Send to FlowState stack or Layer system\n");
        return;
    }

    if(((unsigned long)event.GetType() & (unsigned long)WindowEventType::RENDERER_EVENTS) > 0)
    {
        printf("Send to renderer\n");
        return;
    };
}

void Workshop::Run() {
    while(m_running)
    {
        m_window->Update();
    }
}