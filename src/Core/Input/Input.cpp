//
// Created by Jack Davidson on 11/08/2020.
//

#include "Input.h"
#include "../WindowEvent.h"
#include "../../Utils/DebugUtils.h"

/// Update Key presses from last frame to held, Update releases from last frame to none
///
void Input::Update()
{
    for (Status& status : s_keyStatus)
    {
        if(((unsigned long)status & (unsigned long)Status::UP) > 0)
        {
            status = Status::NONE;
        }
        else if(status == Status::DOWN)
        {
            status = Status::HELD;
        }
    }
    for (Status& status : s_mouseStatus)
    {
        if(((unsigned long)status & (unsigned long)Status::UP) > 0)
        {
            status = Status::NONE;
        }
        else if(status == Status::DOWN)
        {
            status = Status::HELD;
        }
    }
}

void Input::OnEvent(WindowEvent& event)
{
    switch(event.GetType())
    {
        case WindowEventType::KEY_PRESSED:
        {
            KeyPressedEvent keyEvent = static_cast<KeyPressedEvent&>(event);
            s_keyStatus[keyEvent.GetKeyCode()] = Status::DOWN;
            break;
        }
        case WindowEventType::KEY_RELEASED:
        {
            KeyReleasedEvent keyEvent = static_cast<KeyReleasedEvent&>(event);
            char current = (char)s_keyStatus[keyEvent.GetKeyCode()];
            s_keyStatus[keyEvent.GetKeyCode()] = (Status)((current & (char)Status::DOWN) | (char)Status::UP);
            break;
        }
        case WindowEventType::MOUSE_BUTTON_PRESSED:
        {
             MouseButtonPressedEvent mouseEvent = static_cast<MouseButtonPressedEvent&>(event);
             s_mouseStatus[mouseEvent.GetKeyCode()] = Status::DOWN;
            break;
        }
        case WindowEventType::MOUSE_BUTTON_RELEASED:
        {
             MouseButtonReleasedEvent mouseEvent = static_cast<MouseButtonReleasedEvent&>(event);
            s_mouseStatus[mouseEvent.GetKeyCode()] = (Status)((char)s_mouseStatus[mouseEvent.GetKeyCode()] | (char)Status::UP);
            break;
        }
        case WindowEventType::MOUSE_MOVE:
        {
            MouseMoveEvent mouseEvent = static_cast<MouseMoveEvent&>(event);
            s_mousePos = mouseEvent.GetPos();
            break;
        }
        default:
            assertm(false,"Unrecognised Input Event");
    }
}

bool Input::GetKeyDown(int code) {
    return ((unsigned long)s_keyStatus[code] & (unsigned long)Status::DOWN) > 0;
}

bool Input::GetKeyUp(int code) {
    return ((unsigned long)s_keyStatus[code] & (unsigned long)Status::UP) > 0;
}

bool Input::GetKey(int code) {
    return ((unsigned long)s_keyStatus[code] & ((unsigned long)Status::DOWN | (unsigned long)Status::HELD)) > 0;
}

bool Input::GetMouseButtonDown(int code) {
    return ((unsigned long)s_mouseStatus[code] & (unsigned long)Status::DOWN) > 0;
}

bool Input::GetMouseButtonUp(int code) {
    return ((unsigned long)s_mouseStatus[code] & (unsigned long)Status::UP) > 0;
}

bool Input::GetMouseButton(int code) {
    return ((unsigned long)s_mouseStatus[code] & ((unsigned long)Status::DOWN | (unsigned long)Status::HELD)) > 0;
}
