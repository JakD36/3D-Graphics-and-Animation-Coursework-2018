//
// Created by Jack Davidson on 10/05/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_IMGUI_IMPL_GLM_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_IMGUI_IMPL_GLM_H

namespace ImGui
{
    inline bool InputFloat3(const char *label, glm::vec3 &val) noexcept
    {
        float tmp[3] = {val.x,val.y,val.z};
        bool output = ImGui::InputFloat3(label, tmp);
        val = {tmp[0],tmp[1],tmp[2]};
        return output;
    }

    inline bool InputFloat4(const char *label, glm::vec4 &val) noexcept
    {
        float tmp[4] = {val.x,val.y,val.z,val.w};
        bool output = ImGui::InputFloat4(label, tmp);
        val = {tmp[0],tmp[1],tmp[2],tmp[3]};
        return output;
    }
}

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_IMGUI_IMPL_GLM_H
