#include "EngineTime.h"

EngineTime* EngineTime::instance = NULL;

void EngineTime::Initialize()
{
    instance = new EngineTime();
}

void EngineTime::Destroy()
{
    delete instance;
}

double EngineTime::GetTime()
{
    return instance->time;
}

double EngineTime::GetDeltaTime()
{
    return instance->deltaTime;
}

double EngineTime::GetUnscaledTime()
{
    return instance->unscaledTime;
}

double EngineTime::GetUnscaledDeltaTime()
{
    return instance->unscaledDeltaTime;
}

void EngineTime::SetTimeScale(double timeScale)
{
    instance->timeScale = timeScale;
}

EngineTime::EngineTime()
{

}

EngineTime::~EngineTime()
{

}

void EngineTime::LogFrameStart()
{
    instance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
    instance->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = instance->end - instance->start;

    instance->unscaledDeltaTime = elapsedSeconds.count();
    instance->deltaTime = elapsedSeconds.count() * instance->timeScale;

    instance->time += instance->deltaTime;
    instance->unscaledTime += instance->unscaledDeltaTime;

    //std::cout << "Unscaled time is " << instance->unscaledTime << "\n";
    //std::cout << "Frame update finished in " << instance->deltaTime << "\n";
}
