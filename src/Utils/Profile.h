#ifndef Profile_h
#define Profile_h

#include <string>
#include <chrono>
#include <vector>
#include <iostream>
#include <stack>

#include <GLFW/glfw3.h>

#include "../../Include/DearImgui/imgui.h"
#include "../../Include/DearImgui/imgui_impl_glfw.h"
#include "../../Include/DearImgui/imgui_impl_opengl3.h"

using namespace std;

inline ImVec2 add(ImVec2 a, ImVec2 b) { return ImVec2(a.x + b.x, a.y + b.y); }

class ProfileData{
public:
    string m_identifier;
    double m_start;
    double m_length;
    vector<ProfileData*> m_children;
    
    ProfileData();
    ProfileData* Add(string identifier, double start);
    void Draw(ImDrawList* drawList, ImVec2 canvasPos, ImVec2 canvasSize, double rootTime, int depth);        
};

class ProfilerService{
    private:
        ProfilerService();
        static ProfilerService* m_instance;
        float m_start;
        vector<ProfileData*> m_storage;
    public:
        static ProfilerService* GetInstance();
        ProfileData* Add(string identifier, double start);
        void Draw();
        vector<ProfileData*> GetStorage();
};

class Profile{
    public:
        double m_start;
        string m_identifier;
        ProfileData* m_data;

        Profile(string identifier);
        
        ~Profile();
};

#endif