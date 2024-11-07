#include "MenuScreen.h"
#include "../SceneCamera/SceneCameraHandler.h"

MenuScreen::MenuScreen() : UIScreen("MENU_SCREEN")
{

}

MenuScreen::~MenuScreen()
{

}

void MenuScreen::DrawUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			this->ShowMenuFile();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Game Object"))
		{
			this->ShowMenuGameObject();
			ImGui::EndMenu();
		}
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		if (ImGui::SmallButton("Align with View"))
			SceneCameraHandler::AlignGameCamerasToView();
		ImGui::SameLine();
		ImGui::PopStyleColor();

		ImGui::EndMainMenuBar();
	}
	ImGui::PopStyleVar();
}

void MenuScreen::ShowMenuFile()
{
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Save")) {}
	if (ImGui::MenuItem("Save As")) {}
	if (ImGui::MenuItem("Load")) {}
}

void MenuScreen::ShowMenuGameObject()
{
	if (ImGui::MenuItem("Create Quad"))
	{
		GameObjectManager::CreateGameObject(GameObjectManager::QUAD);
	}
	if (ImGui::MenuItem("Create Cube"))
	{
		GameObjectManager::CreateGameObject(GameObjectManager::CUBE);
	}
	if (ImGui::MenuItem("Create Sphere"))
	{

	}
	if (ImGui::MenuItem("Create Game Camera"))
	{
		GameObjectManager::CreateGameObject(GameObjectManager::GAME_CAMERA);
	}
}
