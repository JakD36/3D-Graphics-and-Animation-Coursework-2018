//
// Created by Jack Davidson on 09/08/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOWEVENT_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOWEVENT_H

enum class WindowEventType
{
    WINDOW_RESIZE = 1 << 0,
    FRAMEBUFFER_RESIZE = 1 << 1,
    KEY_PRESSED = 1 << 2,
    KEY_RELEASED = 1 << 3,
    MOUSE_MOVE = 1 << 4,
    MOUSE_BUTTON_PRESSED = 1 << 5,
    MOUSE_BUTTON_RELEASED = 1 << 6,


    RENDERER_EVENTS = WINDOW_RESIZE | FRAMEBUFFER_RESIZE,
    KEY_EVENTS = KEY_PRESSED | KEY_RELEASED,
    MOUSE_EVENTS = MOUSE_MOVE | MOUSE_BUTTON_RELEASED | MOUSE_BUTTON_PRESSED,
};

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

class MouseMove : public WindowEvent
{
private:
    int m_x,m_y;
public:
    MouseMove(float x, float y) : m_x(x), m_y(y);
    int GetX() {return m_x;};
    int GetY() {return m_y;};
    WindowEventType GetType() const final {return WindowEventType::MOUSE_MOVE;};
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WINDOWEVENT_H
