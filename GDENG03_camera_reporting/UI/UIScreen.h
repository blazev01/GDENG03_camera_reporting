#pragma once
#include "string";
#include "../IMGUI/imgui.h"
#include "../IMGUI/imgui_impl_dx11.h"
#include "../IMGUI/imgui_impl_win32.h"
#include "../WindowSystem/Window.h"

class UIManager;

class UIScreen
{
protected:
	UIScreen(std::string name);
	~UIScreen();

	std::string GetName();
	virtual void DrawUI() = 0;

	std::string name;
	bool enabled = true;

	friend class UIManager;
};

