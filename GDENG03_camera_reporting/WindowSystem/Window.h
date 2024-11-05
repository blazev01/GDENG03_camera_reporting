#pragma once
#include "Windows.h"

class Window
{
public:
	Window();
	~Window();

	bool Init();
	bool Broadcast();
	bool Release();
	bool IsRunning();

	RECT GetWindowRect();
	void SetHWND(HWND hwnd);

	virtual void OnCreate() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnFocus() = 0;
	virtual void OnKillFocus() = 0;
	virtual void OnDestroy();
	
protected:
	HWND hwnd;
	bool isRunning;
};

