//
// Created by Jack Davidson on 26/01/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DRAWMESHCOMMAND_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DRAWMESHCOMMAND_H

class DrawMeshCommand : public RenderCommand
{
public:
    DrawMeshCommand() : RenderCommand(Type::DRAW_MESH,1){}
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DRAWMESHCOMMAND_H