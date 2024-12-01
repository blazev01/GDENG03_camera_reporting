#include "OutlinerScreen.h"
#include "../GameObjects/GameObjectManager.h"

#include <algorithm>

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
			ImGuiMultiSelectFlags msFlags =
				ImGuiMultiSelectFlags_SelectOnClick |
				ImGuiMultiSelectFlags_ClearOnClickVoid;		

			for (int i = 0; i < gameObjects.size(); i++)
			{
				const std::string& objectName = gameObjects[i]->GetName();

				std::string lowObjName = objectName;
				std::string lowSrcText = searchText;

				std::transform(lowObjName.begin(), lowObjName.end(), lowObjName.begin(), ::tolower);
				std::transform(lowSrcText.begin(), lowSrcText.end(), lowSrcText.begin(), ::tolower);

				if (!lowSrcText.empty() && lowObjName.find(lowSrcText) == std::string::npos)
					continue;

				bool selected = this->selection[i];
				if (ImGui::Selectable(gameObjects[i]->GetName().c_str(), &selected))
				{
					if (!ImGui::GetIO().KeyCtrl)
					{
						std::fill(this->selection.begin(), this->selection.end(), false);
						GameObjectManager::ClearSelection();
					}

					this->selection[i] = selected;
					if (selected) GameObjectManager::AddSelectedObject(gameObjects[i]);
					else GameObjectManager::RemoveSelectedObject(gameObjects[i]);
				}

			}
		}
	}
	ImGui::End();
}
