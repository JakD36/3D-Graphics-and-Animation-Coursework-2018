//
// Created by Jack Davidson on 14/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASKRESOURCE_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASKRESOURCE_H

#include <vector>
#include "../RenderPass.h"
#include <string>

class RenderTaskResource : public Resource{
public:
    std::vector<RenderPass> m_passes;
    std::string m_name;
    RenderTaskResource(std::string filepath);
    void Reset(std::string filepath);
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASKRESOURCE_H
