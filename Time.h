#pragma once
#include <SDL.h>


class Time sealed
{
private:
    static double timeSinceStart;
    static double timeScale;
    static double deltaTime;
    static Uint64 NOW, LAST;

public:
    static void Calculate(void);
    static void SetTimeScale(double _timeScale);
    static void SetNow(Uint64 _NOW);
    static double GetTimeScale(void);
    static double GetTimeSinceStart(void);
    static double GetDeltaTime(void);
};