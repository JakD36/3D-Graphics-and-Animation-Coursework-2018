//
// Created by Jack Davidson on 08/08/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOW_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOW_H

#include <string>
#include <functional>

class WindowEvent;

class Window {
protected:
    Window(){};
public:
    Window(std::string title, int width, int height){};
    virtual ~Window(){};
    virtual void RegisterEventListener(std::function<void(WindowEvent& event)> func) = 0;
    virtual void Update() = 0;
    virtual float GetDeltaTime() = 0;
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOW_H
