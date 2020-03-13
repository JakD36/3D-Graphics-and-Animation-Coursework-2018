#ifndef ProfileService_h
#define ProfileService_h

#include <string>

#define PROFILE_SIZE 36000

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

    public:
        static ProfilerService* GetInstance() noexcept;
        
        int StartTimer(std::string identifier) noexcept;
        void StopTimer(int timer) noexcept;
        
        void Draw() noexcept;
};

#endif