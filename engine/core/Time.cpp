#include "Time.h"
#include <chrono>

namespace Pinecone {

    double Time::s_DeltaTime = 0.0;
    double Time::s_LastTime = 0.0;
    double Time::s_TotalTime = 0.0;

    using Clock = std::chrono::high_resolution_clock;

    void Time::Init() {
        s_LastTime = std::chrono::duration<double>(
            Clock::now().time_since_epoch()
        ).count();
    }

    void Time::Update() {
        double now = std::chrono::duration<double>(
            Clock::now().time_since_epoch()
        ).count();

        s_DeltaTime = now - s_LastTime;
        s_LastTime = now;
        s_TotalTime += s_DeltaTime;
    }

    float Time::GetDeltaTime() {
        return static_cast<float>(s_DeltaTime);
    }

    float Time::GetTotalTime() {
        return static_cast<float>(s_TotalTime);
    }

}
