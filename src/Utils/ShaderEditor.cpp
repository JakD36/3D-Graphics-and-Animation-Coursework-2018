//
// Created by Jack Davidson on 10/05/2020.
//

#include "ShaderEditor.h"

#include "../Include/DearImgui/imgui.h"
#include "../Include/DearImgui/imgui_impl_opengl3.h"
#include "../Include/DearImgui/imgui_impl_glfw.h"
#include "imgui_impl_glm.h"
#include "../Views/RenderTask.h"
#include "../Views/RenderTaskManager.h"

void ShaderEditorWindow(std::vector<GameObject>& objs)
{
    ImGui::Begin("Shader Tool",NULL);
    if(ImGui::TreeNode("GameObjects"))
    {
        auto tasks = RenderTaskManager::GetInstance()->GetRenderTasks();
        for(int i = 0; i < tasks.size(); ++i)
        {
            if(ImGui::TreeNode(tasks[i]->m_name.c_str()))
            {
                for(int j = 0; j < tasks[i]->m_passes.size();++j)
                {
                    if(ImGui::TreeNode(("Pass " + std::to_string(j)).c_str()))
                    {
                        auto &pass = tasks[i]->m_passes[j];
                        for(int k = 0; k < pass.m_uniformf.size();++k)
                        {
                            ImGui::SliderFloat(pass.m_uniformf[k].m_key.c_str(), &pass.m_uniformf[k].m_value,0,5);
                        }
                        for(int k = 0; k < pass.m_uniform3fv.size();++k)
                        {
                            ImGui::InputFloat3(pass.m_uniform3fv[k].m_key.c_str(), pass.m_uniform3fv[k].m_value);
                        }
                        for(int k = 0; k < pass.m_uniform4fv.size();++k)
                        {
                            ImGui::InputFloat4(pass.m_uniform4fv[k].m_key.c_str(), pass.m_uniform4fv[k].m_value);
                        }
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
    ImGui::End();
}