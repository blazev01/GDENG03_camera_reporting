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
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::SmallButton("File");
		ImGui::SameLine();
		ImGui::SmallButton("Game Object");
		ImGui::SameLine();
		if (ImGui::SmallButton("Align with View"))
			SceneCameraHandler::AlignGameCamerasToView();
		ImGui::SameLine();
		ImGui::PopStyleColor();

		ImGui::EndMainMenuBar();
	}
	ImGui::PopStyleVar();
}
