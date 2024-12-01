#include "OutlinerScreen.h"
#include "../GameObjects/GameObjectManager.h"

OutlinerScreen::OutlinerScreen() : UIScreen("OUTLINER_SCREEN")
{

}

OutlinerScreen::~OutlinerScreen()
{

}

void OutlinerScreen::DrawUI()
{
	static char searchText[256] = "";
	if (ImGui::Begin("Outliner", &this->enabled, ImGuiWindowFlags_NoCollapse))
	{
		ImGui::InputText("Search", searchText, IM_ARRAYSIZE(searchText));

		const std::vector<GameObject*>& gameObjects = GameObjectManager::GetGameObjects();
		if (gameObjects.size() != this->selection.size())
			this->selection.resize(gameObjects.size());

		if (!gameObjects.empty())
		{
			for (int i = 0; i < gameObjects.size(); i++)
			{
				const std::string& objectName = gameObjects[i]->GetName();

				if (strlen(searchText) > 0 && objectName.find(searchText) == std::string::npos)
					continue;

				bool selected = this->selection[i];
				if (ImGui::Selectable(gameObjects[i]->GetName().c_str(), &selected))
				{
					if (!ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
						this->ResetSelection();

					if (selected) GameObjectManager::SetSelectedObject(gameObjects[i]);
					else GameObjectManager::SetSelectedObject(NULL);
				}

				this->selection[i] = selected;
			}
		}
	}
	ImGui::End();
}

void OutlinerScreen::ResetSelection()
{
	for (int i = 0; i < this->selection.size(); i++)
		this->selection[i] = false;
}
