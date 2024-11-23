#pragma once
#include "../IMGUI/imgui.h"
#include "../IMGUI/imgui_impl_dx11.h"
#include "../IMGUI/imgui_impl_win32.h"

class CustomStyles
{
public:
	void StyleColorsCrimson();
	void StyleColorsEvangelion();
	void StyleColorsDarkForest();

private:
	ImVec4 Alpha(const ImVec4& color, float a);
};

