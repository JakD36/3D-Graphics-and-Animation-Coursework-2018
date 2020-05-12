//
// Created by Jack Davidson on 10/05/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASK_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASK_H

#include <vector>
#include "../RenderPass.h"

class RenderTask
{
public:
    std::string m_name;
    std::vector<RenderPass> m_passes;
    RenderTask();
    RenderTask(std::string filepath);
    void Reset(std::string filepath);
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASK_H
