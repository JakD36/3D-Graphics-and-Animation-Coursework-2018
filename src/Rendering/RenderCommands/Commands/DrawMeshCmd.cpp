//
// Created by Jack on 04/03/2021.
//

#include "DrawMeshCmd.h"

DrawMeshCmd::DrawMeshCmd() noexcept
    : RenderCommand(Type::DRAW_MESH, 1)
{
}