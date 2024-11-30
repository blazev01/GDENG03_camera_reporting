#pragma once
#include "UINames.h"
#include "../GraphicsEngine/DeviceContext.h"

class UIManager
{
public:
	typedef std::vector<UIScreen*> UIList;
	typedef std::unordered_map<std::string, UIScreen*> UITable;

	static void Initialize(HWND hwnd);
	static void Destroy();
	static void DrawAllUI();

	static UIScreen* GetUIScreen(std::string name);
	static bool GetEnabled(std::string name);
	static void SetEnabled(std::string name, bool enabled);

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;

private:
	UIManager(HWND hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};

	static UIManager* instance;

	UIList uiList;
	UITable uiTable;
};

