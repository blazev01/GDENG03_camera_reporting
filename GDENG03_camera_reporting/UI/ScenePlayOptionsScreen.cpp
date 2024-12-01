#include "ScenePlayOptionsScreen.h"
#include "../Backend/EngineBackend.h"
#include "../GameObjects/GameObjectManager.h"

ScenePlayOptionsScreen::ScenePlayOptionsScreen() : UIScreen("SCENE_PLAY_OPTIONS_SCREEN")
{

}

ScenePlayOptionsScreen::~ScenePlayOptionsScreen()
{

}

void ScenePlayOptionsScreen::DrawUI()
{
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoDocking;

	if (ImGui::Begin("Scene Play Options", (bool*)0, flags))
	{
		if (EngineBackend::GetMode() == EngineBackend::EDITOR)
		{
			if (ImGui::Button("Play"))
			{
				GameObjectManager::SaveEditStates();
				EngineBackend::SetEditorMode(EngineBackend::PLAY);
			}
		}
		else
		{
			if (ImGui::Button("Stop"))
			{
				GameObjectManager::RestoreEditStates();
				EngineBackend::SetEditorMode(EngineBackend::EDITOR);
			}
		}

		if (EngineBackend::GetMode() == EngineBackend::PAUSED)
		{
			ImGui::SameLine();
			if (ImGui::Button("Resume"))
			{
				EngineBackend::SetEditorMode(EngineBackend::PLAY);
			}
		}
		else
		{
			ImGui::SameLine();
			ImGui::BeginDisabled(EngineBackend::GetMode() != EngineBackend::PLAY);
			if (ImGui::Button("Pause "))
			{
				EngineBackend::SetEditorMode(EngineBackend::PAUSED);
			}
			ImGui::EndDisabled();
		}

		ImGui::SameLine();
		ImGui::BeginDisabled(EngineBackend::GetMode() != EngineBackend::PAUSED);
		if (ImGui::Button("Frame Step"))
		{
			EngineBackend::StartFrameStep();
		}
		ImGui::EndDisabled();
	}
	ImGui::End();
}
