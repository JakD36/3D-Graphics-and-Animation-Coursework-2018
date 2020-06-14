//
// Created by Jack Davidson on 10/05/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASK_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASK_H

#include "RenderTaskResource.h"

class RenderTask
{
private:
    size_t m_key;
    ResourceManager<RenderTaskResource>* m_manager;
public:
    RenderTask(std::string filepath);
    RenderTask(const RenderTask &cp);
    ~RenderTask();

    size_t size();
    RenderPass& operator[](const size_t& index) noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASK_H
