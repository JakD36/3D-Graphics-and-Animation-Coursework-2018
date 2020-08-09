//
// Created by Jack Davidson on 08/08/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WORKSHOP_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WORKSHOP_H


#include "Core/Application/Application.h"

class Workshop : public Application{
public:
    Workshop();
    ~Workshop() final;
    void OnEvent(WindowEvent& event) final;
    void Run() final;
};



#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_WORKSHOP_H
