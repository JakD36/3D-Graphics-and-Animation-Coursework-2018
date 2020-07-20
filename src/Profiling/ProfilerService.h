#ifndef ProfileService_h
#define ProfileService_h

#include <string>

#define PROFILE_SIZE 36000

#ifndef NDEBUG
#define PROFILE(timer,title) int timer = ProfilerService::GetInstance()->StartTimer(title);
#define ENDPROFILE(timer) ProfilerService::GetInstance()->StopTimer(timer);
#else
#define PROFILE(timer,title) //Used only when ifndef NDEBUG
#define ENDPROFILE(timer) //Used only when ifndef NDEBUG
#endif

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

        ProfilerService() noexcept;
        inline static ProfilerService* m_instance = NULL;
        float m_start;
        int m_index;
        int m_nextDepth;
        double m_windowTime;
        double m_maxRewindTime;
        float m_canvasWidth;
        ProfileData m_storage[PROFILE_SIZE];

        bool m_recording = true;
        float m_recordEndTime;

    public:
        static ProfilerService* GetInstance() noexcept;
        
        int StartTimer(std::string identifier) noexcept;
        void StopTimer(int timer) noexcept;
        
        void Draw() noexcept;
};

#endif