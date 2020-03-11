#ifndef ProfileService_h
#define ProfileService_h

#include <string>
#include <chrono>
#include <vector>
#include <iostream>
#include <stack>

#include <GLFW/glfw3.h>

#include "../../Include/DearImgui/imgui.h"
#include "../../Include/DearImgui/imgui_impl_glfw.h"
#include "../../Include/DearImgui/imgui_impl_opengl3.h"

#define PROFILE_SIZE 36000

inline ImVec2 add(ImVec2 a, ImVec2 b) { return ImVec2(a.x + b.x, a.y + b.y); }

class ProfilerService{
    private:

        enum class Status{
            EMPTY,
            RECORDING,
            COMPLETE
        };

        struct ProfileData{
            std::string Identifier;
            double Start;
            double Length;
            int Depth;
            Status Status;
        };

        ProfilerService();
        inline static ProfilerService* m_instance = NULL;
        float m_start;
        int m_index;
        int m_nextDepth;
        double m_windowTime;
        double m_maxRewindTime;
        float m_canvasWidth;
        ProfileData m_storage[PROFILE_SIZE];

    public:
        static ProfilerService* GetInstance();
        
        int StartTimer(std::string identifier);
        void StopTimer(int timer);
        
        void Draw();      
};

#endif