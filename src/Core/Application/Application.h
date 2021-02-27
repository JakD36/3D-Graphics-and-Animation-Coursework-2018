//
// Created by Jack Davidson on 08/08/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_APPLICATION_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_APPLICATION_H

#include <memory>
#include "Window.h"
#include "../../Utils/DebugUtils.h"

class WindowEvent;

class Application {
protected:
    inline static Application* s_instance = nullptr;
    bool m_running = true;
    std::unique_ptr<Window> m_window;

    Application() {
        ASSERT(s_instance == nullptr,"Application already exists")
        s_instance = this;
    };
    virtual ~Application() {};
public:
    virtual void OnEvent(WindowEvent& event) = 0;
    virtual void Run() = 0;
};

Application* CreateApplication() noexcept;


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_APPLICATION_H
