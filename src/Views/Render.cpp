#include "Render.hpp"

void RenderManager::QueueToAddOrUpdate(GameObject* in_gameObject)
{
    m_addUpdateQueue.push(in_gameObject);
}

void RenderManager::QueueToRemove(GameObject* in_gameObject)
{
    m_removeQueue.push(in_gameObject);
}

void RenderManager::Batch()
{   
    int profiler = ProfilerService::GetInstance()->StartTimer("Render Batch");
    while(!m_addUpdateQueue.empty())
    {
        GameObject* next = m_addUpdateQueue.front();
        
        bool match = false;

        for(m_iterator = m_renderList.begin(); m_iterator != m_renderList.end(); ++m_iterator)
        {
            if( (*m_iterator)->m_mesh == next->m_mesh )
            {
                match = true;
                if( (*m_iterator)->m_texture == next->m_texture)
                {
                    m_renderList.insert(m_iterator,next);
                    match = false;
                    break;
                }
            }
            else
            {
                if(match)
                {
                    m_renderList.insert(m_iterator,next);
                    match = false;
                    break;
                }
            }
        }
        if(m_iterator == m_renderList.end())
        {
            m_renderList.push_back(next);   
        }
        m_addUpdateQueue.pop();
    }

    cout<<"Batched List!"<<endl;
    for(m_iterator = m_renderList.begin(); m_iterator != m_renderList.end(); ++m_iterator)
    {
        cout<<(*m_iterator)->m_mesh<<" "<<(*m_iterator)->m_texture<<endl;
    }
    ProfilerService::GetInstance()->StopTimer(profiler);
}