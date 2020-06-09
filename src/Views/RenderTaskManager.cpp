//
// Created by Jack Davidson on 10/05/2020.
//

#include "RenderTaskManager.h"
#include <algorithm>
#include <sys/stat.h>

using namespace std;

void RenderFileInfo::ResetIfModified()
{
    struct stat buf;
    stat(m_key.c_str(),&buf);

    if(buf.st_mtime != m_lastModified) // File has been modified
    {
        m_renderTask.reset(new RenderTask(m_key));
    }
}

RenderTaskManager::RenderTaskManager() noexcept {}
RenderTaskManager::RenderTaskManager(const RenderTaskManager &cp) noexcept {};

RenderTaskManager* RenderTaskManager::GetInstance() noexcept
{
    if(m_instance == nullptr)
    {
        m_instance = new RenderTaskManager;
    }
    return m_instance;
}

RenderTask* RenderTaskManager::RequestRenderTask(string path) noexcept
{
    auto iter = find_if(begin(m_renderTaskInfo),end(m_renderTaskInfo),[&](auto &info){ return info->m_key == path; });

    if(iter == end(m_renderTaskInfo)) // Create new RenderTask
    {
        struct stat buf;
        stat(path.c_str(),&buf);

        m_renderTaskInfo.push_back(make_unique<RenderFileInfo>(RenderFileInfo
        {
            path,
            buf.st_mtime,
            make_unique<RenderTask>(path)
        }));
        return m_renderTaskInfo[m_renderTaskInfo.size()-1]->m_renderTask.get();
    }
    else // Return the found task
    {
        return iter->get()->m_renderTask.get();
    }
}

void RenderTaskManager::TryUpdateFiles() noexcept
{
    for_each(begin(m_renderTaskInfo),end(m_renderTaskInfo),[](unique_ptr<RenderFileInfo> &x)
    {
        x->ResetIfModified();
    });
}

std::vector<RenderTask*> RenderTaskManager::GetRenderTasks()
{
    std::vector<RenderTask*> output(m_renderTaskInfo.size());
    output.reserve(m_renderTaskInfo.size());
    transform(begin(m_renderTaskInfo),end(m_renderTaskInfo),
            begin(output),[](auto &x){return x->m_renderTask.get();});
    return output;
}