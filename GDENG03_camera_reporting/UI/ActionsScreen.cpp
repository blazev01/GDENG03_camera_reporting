#include "ActionsScreen.h"
#include "../Backend/ActionHistory.h"
#include "../GameObjects/GameObjectManager.h"

ActionsScreen::ActionsScreen() : UIScreen("ACTIONS_SCREEN")
{

}

ActionsScreen::~ActionsScreen()
{

}

void ActionsScreen::DrawUI()
{
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoResize;

	if (ImGui::Begin("Actions", (bool*)0, flags))
	{
		ImGui::BeginDisabled(!ActionHistory::HasRemainingUndoActions());
		if (ImGui::Button("Undo"))
		{
			EditorAction* action = ActionHistory::UndoAction();
			if (action) this->SetGameObjectData(action);
		}
		ImGui::EndDisabled();

		ImGui::SameLine();
		ImGui::BeginDisabled(!ActionHistory::HasRemainingRedoActions());
		if (ImGui::Button("Redo"))
		{
			EditorAction* action = ActionHistory::RedoAction();
			if (action) this->SetGameObjectData(action);
		}
		ImGui::EndDisabled();

		ImGui::End();
	}
}

void ActionsScreen::SetGameObjectData(EditorAction* action)
{
	GameObject* gameObject = GameObjectManager::FindGameObject(action->GetOwnerName());

	gameObject->SetPosition(action->GetStoredPosition());
	gameObject->SetRotation(action->GetStoredRotation());
	gameObject->SetScale(action->GetStoredScale());
	gameObject->SetTransform(action->GetStoredMatrix());
}
