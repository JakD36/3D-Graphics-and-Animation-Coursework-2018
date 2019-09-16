#include "Profile.h"

ProfilerService::ProfilerService(){
    m_storage = vector<ProfileData*>();
    m_storage.reserve(7200);
    m_start = glfwGetTime();
}

ProfilerService* ProfilerService::GetInstance(){
    if (m_instance == NULL){
        m_instance = new ProfilerService();
    }
    return m_instance;
}

ProfileData* ProfilerService::Add(string identifier, double start){
    if(m_storage.size() == 0 || m_storage[m_storage.size()-1]->m_length >= 0.0){
        ProfileData* data = new ProfileData();
        data->m_identifier = identifier;
        data->m_start = start;
        m_storage.push_back(data);
        return data;
    }else{
        return m_storage[m_storage.size()-1]->Add(identifier,start);
    }
}

void ProfilerService::Draw(){
    ImGui::Begin("Profiler");
    
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 canvasPos = ImGui::GetCursorScreenPos();
    ImVec2 canvasSize = ImGui::GetContentRegionAvail();
    
    for(int n = 0; n < m_storage.size(); ++n){
        m_storage[n]->Draw(drawList, canvasPos, canvasSize,1.0,0);
    }
    ImGui::End();
}

vector<ProfileData*> ProfilerService::GetStorage(){
    return m_storage;
}