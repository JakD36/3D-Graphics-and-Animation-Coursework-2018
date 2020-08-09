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
    if(((int)event.GetType() & (int)WindowEventType::RENDERER_EVENTS) > 0)
    {
        printf("Window Event occurred");
    };
}

void Workshop::Run() {
    while(m_running)
    {
        m_window->Update();
    }
}