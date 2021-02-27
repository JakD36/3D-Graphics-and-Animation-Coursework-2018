//
// Created by Jack Davidson on 14/06/2020.
//

#include "RenderTaskResource.h"
#include <json.hpp>
#include <fstream>
#include "../../Utils/DebugUtils.h"

RenderTaskResource::RenderTaskResource(std::string filepath) : Resource(filepath) {Reset(filepath);}

void RenderTaskResource::Reset(std::string filepath)
{
    m_passes.clear();

    nlohmann::json js;
    std::fstream file(filepath);
    ASSERT(file.is_open(),"RenderPass Json file did not open.");
    file >> js;

    m_name = js["name"];

    nlohmann::json passes = js["pass"];
    m_passes.reserve(passes.size());
    for(int i = 0; i < passes.size(); ++i)
    {
        m_passes.push_back(RenderPass(passes[i]));
    }
}