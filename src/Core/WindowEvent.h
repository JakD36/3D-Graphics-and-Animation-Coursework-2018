//
// Created by Jack Davidson on 09/08/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOWEVENT_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOWEVENT_H

#include <glm/glm.hpp>
#include "EnumBitmask.h"

enum class WindowEventType : unsigned long
{

    WINDOW_RESIZE = 1 << 0,
    FRAMEBUFFER_RESIZE = 1 << 1,
    KEY_PRESSED = 1 << 2,
    KEY_RELEASED = 1 << 3,
    MOUSE_MOVE = 1 << 4,
    MOUSE_BUTTON_PRESSED = 1 << 5,
    MOUSE_BUTTON_RELEASED = 1 << 6,

    WINDOW_CLOSE = 1 << 7,


    RENDERER_EVENTS = WINDOW_RESIZE | FRAMEBUFFER_RESIZE,
    KEY_EVENTS = KEY_PRESSED | KEY_RELEASED,
    MOUSE_EVENTS = MOUSE_MOVE | MOUSE_BUTTON_RELEASED | MOUSE_BUTTON_PRESSED,
};

ENABLE_BITMASK_OPERATORS(WindowEventType)

#define EVENT_CLASS_TYPE(type) static MsgType GetStaticType() { return MsgType::type; }\
                    virtual MsgType GetEventType() const override { return GetStaticType(); }\

class WindowEvent
{
protected:
    WindowEvent() noexcept {};
public:
    virtual WindowEventType GetType() const = 0;
};

class WindowResizeEvent : public WindowEvent
{
private:
    int w,h;
public:
    WindowResizeEvent(int w, int h){w = w; h = h;};
    int GetWidth() {return w;};
    int GetHeight() {return h;};
    WindowEventType GetType() const final {return WindowEventType::WINDOW_RESIZE;};
};

class FramebufferResizeEvent : public WindowEvent
{
private:
    int w,h;
public:
    FramebufferResizeEvent(int w, int h){w = w; h = h;};
    int GetWidth() {return w;};
    int GetHeight() {return h;};
    WindowEventType GetType() const final {return WindowEventType::FRAMEBUFFER_RESIZE;};
};

class MouseMoveEvent : public WindowEvent
{
private:
    glm::vec2 m_pos;
public:
    MouseMoveEvent(float x, float y) : m_pos(x,y) {};
    glm::vec2 GetPos() {return m_pos;};
    WindowEventType GetType() const final {return WindowEventType::MOUSE_MOVE;};
};

class MouseButtonPressedEvent : public WindowEvent
{
private:
    int m_keyCode;
public:
    MouseButtonPressedEvent(int keyCode) : m_keyCode(keyCode) {};
    int GetKeyCode() {return m_keyCode;};
    WindowEventType GetType() const final {return WindowEventType::MOUSE_BUTTON_PRESSED;};
};

class MouseButtonReleasedEvent : public WindowEvent
{
private:
    int m_keyCode;
public:
    MouseButtonReleasedEvent(int keyCode) : m_keyCode(keyCode) {};
    int GetKeyCode() {return m_keyCode;};
    WindowEventType GetType() const final {return WindowEventType::MOUSE_BUTTON_RELEASED;};
};

class KeyPressedEvent : public WindowEvent
{
private:
    int m_keyCode;
public:
    KeyPressedEvent(int keyCode) : m_keyCode(keyCode) {};
    int GetKeyCode() {return m_keyCode;};
    WindowEventType GetType() const final {return WindowEventType::KEY_PRESSED;};
};

class KeyReleasedEvent : public WindowEvent
{
private:
    int m_keyCode;
public:
    KeyReleasedEvent(int keyCode) : m_keyCode(keyCode) {};
    int GetKeyCode() {return m_keyCode;};
    WindowEventType GetType() const final {return WindowEventType::KEY_RELEASED;};
};

class WindowCloseEvent : public WindowEvent
{
public:
    WindowCloseEvent() {};
    WindowEventType GetType() const final {return WindowEventType::WINDOW_CLOSE;};
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOWEVENT_H
