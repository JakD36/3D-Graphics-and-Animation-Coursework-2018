//
// Created by Jack Davidson on 14/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RESOURCE_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RESOURCE_H

#include <string>

class Resource{
public:
    std::string m_key;
    time_t m_lastModified;
    int m_count;

    Resource(std::string filepath);
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RESOURCE_H
