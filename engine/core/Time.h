#pragma once

namespace Pinecone {

    class Time {
    public:
        static void Init();
        static void Update();
        static float GetDeltaTime();     // seconds
        static float GetTotalTime();     // seconds

    private:
        static double s_DeltaTime;
        static double s_LastTime;
        static double s_TotalTime;
    };

}