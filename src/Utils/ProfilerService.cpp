#include "ProfileService.h"

ProfilerService::ProfilerService(){
    m_index = 0;
    m_nextDepth = 0;
    m_maxRewindTime = 5.0;
    m_windowTime = m_maxRewindTime;
    m_canvasWidth = -1.0f;
    for(int i = 0; i < PROFILE_SIZE; ++i){
        m_storage[i].m_length = -1.0;
    }
}

ProfilerService* ProfilerService::GetInstance(){
    if (m_instance == NULL){
        m_instance = new ProfilerService();
    }
    return m_instance;
}

int ProfilerService::StartTimer(string identifier){
    m_storage[m_index].m_identifier = identifier;
    m_storage[m_index].m_start = glfwGetTime();
    m_storage[m_index].m_length = -2.0;
    
    int minusIndex = m_index - 1;
    int prevIndex =  minusIndex < 0 ? PROFILE_SIZE - 1 : minusIndex;
    
    m_storage[m_index].Depth = m_nextDepth++;

    int tmp = m_index;
    do{
        m_index = (++m_index) % PROFILE_SIZE;
        if(m_storage[m_index].m_length >= -1.0) // TODO: Change to safer method of stepping forward
            break;
    }while(true);
    
    
    return tmp;
}

void ProfilerService::StopTimer(int timer){
    m_storage[timer].m_length = glfwGetTime() - m_storage[timer].m_start;
    --m_nextDepth;
}

void ProfilerService::Draw(){
    int profiler = ProfilerService::GetInstance()->StartTimer("Draw Profiler");
    
    if(m_canvasWidth >= 0)
        ImGui::SetNextWindowContentWidth(m_canvasWidth);
    ImGui::Begin("Profiler",NULL,ImGuiWindowFlags_AlwaysHorizontalScrollbar);
    
    ImVec2 canvasSize = ImGui::GetContentRegionAvail();

    if(ImGui::Button("Zoom in")){
        m_windowTime *= 0.5;
        m_canvasWidth = canvasSize.x * (m_maxRewindTime / m_windowTime);
    }
        
    ImGui::SameLine();
    
    if(ImGui::Button("Zoom out")){
        m_windowTime *= 2;
        if(m_windowTime > m_maxRewindTime)
            m_windowTime = m_maxRewindTime;
        m_canvasWidth = canvasSize.x * (m_maxRewindTime / m_windowTime);
    }
    ImGui::SameLine();
    
    if(ImGui::Button("Reset")){
        m_windowTime = m_maxRewindTime;
        m_canvasWidth = canvasSize.x * (m_maxRewindTime / m_windowTime);
    }
    
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 canvasPos = ImGui::GetCursorScreenPos();
    
    float barHeight = 20.0f;
    float rowHeight = barHeight + 3.0f;
    float barSpacing = 1.0f;
    //! Least width of bar to display
    float leastWidth = 10.0f;
    //! Bar colour
    ImU32 colBar = IM_COL32(100, 0, 0, 255);
    //! Text colour
    ImU32 colText = IM_COL32(0, 0, 0, 255);
    //! Text padding from the top-left
    ImVec2 textPad(3.0f, 3.0f);

    double startTime = glfwGetTime() - m_maxRewindTime;
    
    for(int n = 0; n < PROFILE_SIZE; ++n){
        if(m_storage[n].m_length > 0){
            float xOffset = canvasSize.x * (-startTime + m_storage[n].m_start) / m_windowTime;
            float width = canvasSize.x * m_storage[n].m_length / m_windowTime; 

            ImVec2 topLeft(
                        canvasPos.x + xOffset + barSpacing,
                        canvasPos.y + (m_storage[n].Depth * rowHeight));
            ImVec2 botRight(
                    canvasPos.x + xOffset + width - barSpacing,
                    canvasPos.y + barHeight + (m_storage[n].Depth * rowHeight));

            drawList->AddRectFilled(topLeft, botRight, colBar);
            
            drawList->AddText(add(topLeft, textPad), colText, m_storage[n].m_identifier.c_str());
        }
        else if(m_storage[n].m_length <= -2.0){
            float xOffset = canvasSize.x * (-startTime + m_storage[n].m_start) / m_windowTime;
            float width = canvasSize.x * (glfwGetTime() - m_storage[n].m_start) / m_windowTime; 

            ImVec2 topLeft(
                        canvasPos.x + xOffset + barSpacing,
                        canvasPos.y + (m_storage[n].Depth * rowHeight));
            ImVec2 botRight(
                    canvasPos.x + xOffset + width - barSpacing,
                    canvasPos.y + barHeight + (m_storage[n].Depth * rowHeight));

            drawList->AddRectFilled(topLeft, botRight, colBar);
            
            drawList->AddText(add(topLeft, textPad), colText, m_storage[n].m_identifier.c_str());
        }
    }
    ImGui::End();
    ProfilerService::GetInstance()->StopTimer(profiler);
}