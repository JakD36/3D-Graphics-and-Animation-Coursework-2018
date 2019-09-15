#include <string>
#include <chrono>
#include <vector>
#include <iostream>
#include <stack>

//#define TIME(name) Profile(name)
#define TIME(name)

using namespace std;

struct ProfileData{
public:
    string Identifier;
    chrono::system_clock::time_point StartTime;
    float Length = -1;
    // ProfileData* Parent;
    // vector<ProfileData*> subProfiles;
};

class ProfilerService{
private:
    ProfilerService(){
        m_storage = vector<ProfileData*>(3600);
    }
    static ProfilerService* m_instance;

    vector<ProfileData*> m_storage;
public:
    static ProfilerService* GetInstance(){
        if (m_instance == NULL){
            m_instance = new ProfilerService();
        }
        return m_instance;
    }

    ProfileData* Add(string identifier,chrono::system_clock::time_point start){
        ProfileData* data = new ProfileData();
        data->Identifier = identifier;
        data->StartTime = start;
        m_storage.push_back(data);
        return data;
    }
};

ProfilerService* ProfilerService::m_instance = NULL;

class Profile{
public:
    chrono::system_clock::time_point m_start;
    string m_identifier;
    float m_length;
    ProfileData* m_storage;

    Profile(string identifier){
        m_identifier = identifier;
        m_start = chrono::system_clock::now();
        m_storage = ProfilerService::GetInstance()->Add(identifier,m_start);   
    }
    
    ~Profile(){
        chrono::system_clock::time_point end = chrono::system_clock::now();
        using FpMilliseconds = std::chrono::duration<float, std::chrono::milliseconds::period>;
        m_length = FpMilliseconds(end-m_start).count();
        m_storage->Length = m_length;
    }
};