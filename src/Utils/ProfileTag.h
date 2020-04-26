//
// Created by Jack Davidson on 23/04/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_PROFILETAG_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_PROFILETAG_H

#include <string>
class ProfilerService;

class ProfileTag {
private:
    ProfilerService* p_service;
    int m_handle;
public:
    ProfileTag(std::string tag);
    ~ProfileTag();
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_PROFILETAG_H
