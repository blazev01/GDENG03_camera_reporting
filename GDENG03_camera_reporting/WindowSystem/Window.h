#pragma once
#include "Windows.h"

class Window
{
public:
	Window();

	bool Init();
	bool Broadcast();
	bool Release();
	bool IsRunning();

	RECT GetWindowRect();
	void SetHWND(HWND hwnd);

	virtual void OnCreate() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnDestroy();

	~Window();

protected:
	HWND hwnd;
	bool isRunning;
};

