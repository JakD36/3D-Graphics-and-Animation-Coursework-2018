//
// Created by Jack Davidson on 07/08/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_GLWINDOW_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_GLWINDOW_H

#include <string>
#include "../Application/Window.h"

class GLFWwindow;

struct WindowData
{
    std::function<void(WindowEvent&  event)> m_eventHandler;
};

class GlWindow : public Window{
private:
    GlWindow();
    inline static unsigned int s_windowCount = 0;
    GLFWwindow* m_window;
    WindowData m_windowData;
public:
    GlWindow(std::string title, int width, int height);
    void RegisterEventListener(std::function<void(WindowEvent& event)> func) final;
    void Update() final;

    ~GlWindow() final;
};




#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_GLWINDOW_H
