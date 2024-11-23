#pragma once
#include "iostream"
#include "chrono"
#include "ctime"

class Window;

class EngineTime
{
public:
	static void Initialize();
	static void Destroy();

	static double GetTime();
	static double GetDeltaTime();
	static double GetUnscaledTime();
	static double GetUnscaledDeltaTime();
	static void SetTimeScale(double timeScale);

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};

	static EngineTime* instance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double time = 0.0;
	double deltaTime = 0.0;
	double unscaledTime = 0.0;
	double unscaledDeltaTime = 0.0;
	double timeScale = 1.0;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;
};

