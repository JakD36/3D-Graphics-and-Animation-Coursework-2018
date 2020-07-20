//
// Created by Jack Davidson on 23/04/2020.
//

#include "ProfileTag.h"
#include "ProfilerService.h"

ProfileTag::ProfileTag(std::string tag)
{
    p_service = ProfilerService::GetInstance();
    m_handle = p_service->StartTimer(tag);
}

ProfileTag::~ProfileTag()
{
    p_service->StopTimer(m_handle);
}