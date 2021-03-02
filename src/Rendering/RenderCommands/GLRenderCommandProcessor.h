//
// Created by Jack on 02/03/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_GLRENDERCOMMANDPROCESSOR_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_GLRENDERCOMMANDPROCESSOR_H

#include "RenderCommandProcessor.h"
#include <memory>
#include <vector>

class Window;
class RenderCommand;

class GLRenderCommandProcessor final: public RenderCommandProcessor
{
    void Process(Window *window, std::vector<std::unique_ptr<RenderCommand>> renderQueue) final;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_GLRENDERCOMMANDPROCESSOR_H
