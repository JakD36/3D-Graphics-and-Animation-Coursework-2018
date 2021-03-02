//
// Created by Jack Davidson on 20/07/2020.
//

#include "ProfilerWindow.h"

#include <imgui.h>
#include "ProfilerService.h"
#include "MemoryProfiler.h"

void DrawProfilerWindow()
{
    if(ImGui::Begin("Profiler"))
    {
        if(ImGui::BeginTabBar("Profiler"))
        {
            if(ImGui::BeginTabItem("Frame Time"))
            {
                ProfilerService::GetInstance()->Draw();
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Memory"))
            {
                auto memProfiler = MemoryProfiler::GetInstance();
                if (ImGui::RadioButton("Bytes", memProfiler->m_sizeType == MemoryProfiler::SizeType::BYTES)) { memProfiler->m_sizeType = MemoryProfiler::SizeType::BYTES; } ImGui::SameLine();
                if (ImGui::RadioButton("KiloBytes", memProfiler->m_sizeType == MemoryProfiler::SizeType::KILOBYTES)) { memProfiler->m_sizeType = MemoryProfiler::SizeType::KILOBYTES; } ImGui::SameLine();
                if (ImGui::RadioButton("MegaBytes", memProfiler->m_sizeType == MemoryProfiler::SizeType::MEGABYTES)) { memProfiler->m_sizeType = MemoryProfiler::SizeType::MEGABYTES; } ImGui::SameLine();
                if(ImGui::Button("Clear Array")) memProfiler->Clear();

                memProfiler->Draw();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();
    }
}