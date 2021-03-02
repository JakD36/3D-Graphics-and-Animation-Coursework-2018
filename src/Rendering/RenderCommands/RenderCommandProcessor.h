//
// Created by Jack on 02/03/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMANDPROCESSOR_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMANDPROCESSOR_H

#include <memory>
#include <vector>

class Window;
class RenderCommand;

class RenderCommandProcessor
{
public:
    virtual void Process(Window *window, std::vector<std::unique_ptr<RenderCommand>> renderQueue) = 0;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMANDPROCESSOR_H
