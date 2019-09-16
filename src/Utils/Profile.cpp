#include "Profile.h"

using namespace std;

Profile::Profile(string identifier){
    m_identifier = identifier;
    m_start = glfwGetTime();//chrono::system_clock::now();
    m_data = ProfilerService::GetInstance()->Add(identifier,m_start);   
}

Profile::~Profile(){
    m_data->m_length = glfwGetTime()-m_start;//FpMilliseconds(end-m_start).count();
}
