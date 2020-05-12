//
// Created by Jack Davidson on 10/05/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASKMANAGER_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASKMANAGER_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <memory>
#include "RenderTask.h"

struct RenderFileInfo
{
public:
    std::string m_key;
    time_t m_lastModified;
    std::unique_ptr<RenderTask> m_renderTask;

    void ResetIfModified();
};

class RenderTaskManager
{
private:
    inline static RenderTaskManager *m_instance = NULL;
    std::vector<std::unique_ptr<RenderFileInfo>> m_renderTaskInfo;
    RenderTaskManager() noexcept;
    RenderTaskManager(const RenderTaskManager &cp) noexcept;
public:
    static RenderTaskManager* GetInstance() noexcept;
    RenderTask* RequestRenderTask(std::string path) noexcept;

    void TryUpdateFiles() noexcept;

    std::vector<RenderTask*> GetRenderTasks();
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTASKMANAGER_H
