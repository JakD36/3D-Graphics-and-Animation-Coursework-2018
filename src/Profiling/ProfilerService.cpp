#include "ProfilerService.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DearImgui/imgui.h"

using namespace std;

ImVec2 add(ImVec2 a, ImVec2 b) noexcept { return ImVec2(a.x + b.x, a.y + b.y); }

ProfilerService::ProfilerService() noexcept{
    m_index = 0;
    m_nextDepth = 0;
    m_maxRewindTime = 5.0;
    m_windowTime = m_maxRewindTime;
    m_canvasWidth = -1.0f;
    for(int i = 0; i < PROFILE_SIZE; ++i){
        m_storage[i].Length = -1.0;
    }
}

ProfilerService* ProfilerService::GetInstance() noexcept{
    if (m_instance == NULL){
        m_instance = new ProfilerService();
    }
    return m_instance;
}

int ProfilerService::StartTimer(string identifier) noexcept{
    if(m_recording)
    {
        m_storage[m_index].Identifier = identifier;
        m_storage[m_index].Start = glfwGetTime();
        m_storage[m_index].Length = -2.0;
        m_storage[m_index].Status = Status::RECORDING;

//    int minusIndex = m_index - 1;
//    int prevIndex =  minusIndex < 0 ? PROFILE_SIZE - 1 : minusIndex;

        m_storage[m_index].Depth = m_nextDepth++;

        int tmp = m_index;
        while(true)
        {
            m_index = (++m_index) % PROFILE_SIZE;
            if(m_storage[m_index].Length >= -1.0) // TODO: Change to safer method of stepping forward
                break;
        }
        return tmp;
    }
    else{
        return -1;
    }
}

void ProfilerService::StopTimer(int timer) noexcept{
    if(timer >= 0)
    {
        m_storage[timer].Length = glfwGetTime() - m_storage[timer].Start;
        --m_nextDepth;
        m_storage[timer].Status = Status::COMPLETE;
    }
}

void ProfilerService::Draw() noexcept{
    PROFILE(p,"Draw Profiler");

    ImGui::Begin("Profiler",NULL);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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
    ImGui::SameLine();

    if(m_recording)
    {
        if(ImGui::Button("Pause")){
            m_recording = false;
            m_recordEndTime = glfwGetTime();
        }
    }
    else{
        if(ImGui::Button("Continue")){
            m_recording = true;
        }
    }


    if(m_canvasWidth >= 0)
        ImGui::SetNextWindowContentWidth(m_canvasWidth);
    ImGui::BeginChild("scrollWindow",ImVec2(0,0),false,ImGuiWindowFlags_AlwaysHorizontalScrollbar);
    
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

    double startTime = (m_recording ?  glfwGetTime() : m_recordEndTime) - m_maxRewindTime;
    
    for(int n = 0; n < PROFILE_SIZE; ++n){
        float timePercentOffset = (-startTime + m_storage[n].Start) / m_windowTime;
        float xOffset = canvasSize.x * timePercentOffset;
        float width = canvasSize.x * m_storage[n].Length / m_windowTime;
        if(m_storage[n].Status == Status::COMPLETE && timePercentOffset + width> 0.f){
            if(width > 1){
                ImVec2 topLeft(
                            canvasPos.x + xOffset + barSpacing,
                            canvasPos.y + (m_storage[n].Depth * rowHeight));
                ImVec2 botRight(
                        canvasPos.x + xOffset + width - barSpacing,
                        canvasPos.y + barHeight + (m_storage[n].Depth * rowHeight));

                drawList->AddRectFilled(topLeft, botRight, colBar);
                
                drawList->AddText(add(topLeft, textPad), colText, m_storage[n].Identifier.c_str());
            }
        }
        else if(m_storage[n].Status == Status::RECORDING){
            float xOffset = canvasSize.x * (-startTime + m_storage[n].Start) / m_windowTime;
            float width = canvasSize.x * (glfwGetTime() - m_storage[n].Start) / m_windowTime; 

            ImVec2 topLeft(
                        canvasPos.x + xOffset + barSpacing,
                        canvasPos.y + (m_storage[n].Depth * rowHeight));
            ImVec2 botRight(
                    canvasPos.x + xOffset + width - barSpacing,
                    canvasPos.y + barHeight + (m_storage[n].Depth * rowHeight));

            drawList->AddRectFilled(topLeft, botRight, colBar);
            
            drawList->AddText(add(topLeft, textPad), colText, m_storage[n].Identifier.c_str());
        }
    }
    ImGui::EndChild();
    ImGui::End();
    ENDPROFILE(p);
}
