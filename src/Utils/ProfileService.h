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

#define PROFILE_SIZE 7200

using namespace std;

inline ImVec2 add(ImVec2 a, ImVec2 b) { return ImVec2(a.x + b.x, a.y + b.y); }

struct ProfileData{
    string m_identifier;
    double m_start;
    double m_length;
    int Depth;
};

class ProfilerService{
    private:
        ProfilerService();
        static ProfilerService* m_instance;
        float m_start;
        int m_index;
        int m_nextDepth;
        ProfileData m_storage[PROFILE_SIZE];

    public:
        static ProfilerService* GetInstance();
        
        int StartTimer(string identifier);
        void StopTimer(int timer);
        
        void Draw();      
};

#endif