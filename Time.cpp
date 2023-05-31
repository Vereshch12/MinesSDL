#include <SDL.h>
#include "Time.h"

double Time::timeSinceStart = 0;
double Time::deltaTime = 0;
double Time::timeScale = 1;
Uint64 Time::NOW = 0;
Uint64 Time::LAST = 0;

void Time::Calculate(void)
{
    LAST = NOW;
    SetNow(SDL_GetPerformanceCounter());
    deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency()) * timeScale;
    timeSinceStart += deltaTime;
}

void Time::SetTimeScale(double _timeScale)
{
    timeScale = _timeScale < 0 ? 0 : _timeScale;
}

void Time::SetNow(Uint64 _NOW)
{
    NOW = _NOW;
}

double Time::GetTimeScale(void)
{
    return timeScale;
}

double Time::GetTimeSinceStart(void)
{
    return timeSinceStart;
}

double Time::GetDeltaTime(void)
{
	return deltaTime;
}