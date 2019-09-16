#include "Profile.h"

ProfileData::ProfileData(){
    m_children = vector<ProfileData*>();
    m_length = -1.0;
}

ProfileData* ProfileData::Add(string identifier, double start){
    if(m_children.size() == 0 || m_children[m_children.size()-1]->m_length >= 0.0f){    
        ProfileData* data = new ProfileData();
        data->m_identifier = identifier;
        data->m_start = start;
        m_children.push_back(data);
        return data;
    }else{
        return m_children[m_children.size()-1]->Add(identifier,start);
    }
}

void ProfileData::Draw(ImDrawList* drawList, ImVec2 canvasPos, ImVec2 canvasSize, double rootTime, int depth){
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
    
    float xOffset = canvasSize.x * m_start / rootTime;
    if(m_length > 0){
        float width = canvasSize.x * m_length / rootTime;
        
        ImVec2 topLeft(
                    canvasPos.x + xOffset + barSpacing,
                    canvasPos.y + (depth * rowHeight));
        ImVec2 botRight(
                canvasPos.x + xOffset + width - barSpacing,
                canvasPos.y + barHeight + (depth * rowHeight));

        drawList->AddRectFilled(topLeft, botRight, colBar);
        
        drawList->AddText(add(topLeft, textPad), colText, m_identifier.c_str());
    }
    
    for(int n = 0; n < m_children.size(); ++n){
        m_children[n]->Draw(drawList,canvasPos,canvasSize,10,depth+1);
    }
}
