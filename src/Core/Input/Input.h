//
// Created by Jack Davidson on 11/08/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_INPUT_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_INPUT_H

#include "MouseCodes.h"
#include "KeyCodes.h"
#include <glm/glm.hpp>

class WindowEvent;

class Input
{
private:
    enum class Status : char
    {
        NONE = 0,
        DOWN = 1 << 0,
        HELD = 1 << 1,
        UP = 1 << 2,
    };
private:
    inline static Status s_keyStatus[384]; // TODO: Not happy with this setup, Unsure if I should use my own keycode enum, and convert every input to that or just have a larger array of key status
    inline static Status s_mouseStatus[12];

    inline static glm::vec2 s_mousePos;
public:
    static void Update();
    static void OnEvent(WindowEvent& event);
    static bool GetKeyDown(int code);
    static bool GetKeyUp(int code);
    static bool GetKey(int code);

    static bool GetMouseButtonDown(int code);
    static bool GetMouseButtonUp(int code);
    static bool GetMouseButton(int code);
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_INPUT_H
