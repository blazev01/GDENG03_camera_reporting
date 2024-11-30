#include "UIManager.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "CustomStyles.h"
#include "ProfilerScreen.h"
#include "MenuScreen.h"
#include "InspectorScreen.h"
#include "OutlinerScreen.h"
#include "CameraViewportScreen.h"
#include "CreditsScreen.h"
#include "ColorPickerScreen.h"
#include "ScenePlayOptionsScreen.h"
#include "ActionsScreen.h"
#include "ConsoleScreen.h"

UIManager* UIManager::instance = NULL;

void UIManager::Initialize(HWND hwnd)
{
	instance = new UIManager(hwnd);
}

void UIManager::Destroy()
{
	if (!instance->uiList.empty())
	{
		for (int i = instance->uiList.size() - 1; i >= 0; i--)
			delete instance->uiList[i];

		instance->uiTable.clear();
		instance->uiList.clear();
	}

	delete instance;
}

void UIManager::DrawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < instance->uiList.size(); i++)
	{
		if (instance->uiList[i]->enabled)
			instance->uiList[i]->DrawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

UIScreen* UIManager::GetUIScreen(std::string name)
{
	return instance->uiTable[name];
}

bool UIManager::GetEnabled(std::string name)
{
	UIScreen* ui = instance->uiTable[name];
	return ui ? ui->enabled : false;
}

void UIManager::SetEnabled(std::string name, bool enabled)
{
	UIScreen* ui = instance->uiTable[name];
	if (ui) ui->enabled = enabled;
}

UIManager::UIManager(HWND hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::GetDevice(), GraphicsEngine::GetImmediateDeviceContext()->GetDeviceContext());

	CustomStyles styles;
	styles.StyleColorsCrimson();

	UINames uiNames;
	MenuScreen* menuScreen = new MenuScreen();
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);

	OutlinerScreen* outlinerScreen = new OutlinerScreen();
	this->uiTable[uiNames.OUTLINER_SCREEN] = outlinerScreen;
	this->uiList.push_back(outlinerScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);

	CameraViewportScreen* cameraViewportScreen = new CameraViewportScreen();
	this->uiTable[uiNames.CAMERA_VIEWPORT_SCREEN] = cameraViewportScreen;
	this->uiList.push_back(cameraViewportScreen);

	CreditsScreen* creditsScreen = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen();
	this->uiTable[uiNames.COLOR_PICKER_SCREEN] = colorPickerScreen;
	this->uiList.push_back(colorPickerScreen);
	
	ScenePlayOptionsScreen* scenePlayOptionsScreen = new ScenePlayOptionsScreen();
	this->uiTable[uiNames.SCENE_PLAY_OPTIONS_SCREEN] = scenePlayOptionsScreen;
	this->uiList.push_back(scenePlayOptionsScreen);
	
	ActionsScreen* actionsScreen = new ActionsScreen();
	this->uiTable[uiNames.ACTIONS_SCREEN] = actionsScreen;
	this->uiList.push_back(actionsScreen);
	
	ConsoleScreen* consoleScreen = new ConsoleScreen();
	this->uiTable[uiNames.CONSOLE_SCREEN] = consoleScreen;
	this->uiList.push_back(consoleScreen);

}

UIManager::~UIManager()
{

}
