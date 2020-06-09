//
// Created by Jack Davidson on 10/05/2020.
//

#include <json.hpp>
#include <fstream>
#include "RenderTask.h"
#include "../Utils/DebugUtils.h"

RenderTask::RenderTask(){}

RenderTask::RenderTask(std::string filepath){Reset(filepath);}

void RenderTask::Reset(std::string filepath)
{
    m_passes.clear();

    nlohmann::json js;
    std::fstream file(filepath);
    assertm(file.is_open(),"RenderPass Json file did not open.");
    file >> js;

    m_name = js["name"];

    nlohmann::json passes = js["pass"];
    m_passes.reserve(passes.size());
    for(int i = 0; i < passes.size(); ++i)
    {
        m_passes.push_back(RenderPass(passes[i]));
    }
}