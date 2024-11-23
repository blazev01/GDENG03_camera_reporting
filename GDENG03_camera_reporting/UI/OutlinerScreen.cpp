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
	if (ImGui::Begin("Outliner", &this->enabled, ImGuiWindowFlags_NoCollapse))
	{
		const std::vector<GameObject*>& gameObjects = GameObjectManager::GetGameObjects();
		if (gameObjects.size() != this->selection.size())
			this->selection.resize(gameObjects.size());

		if (!gameObjects.empty())
		{
			for (int i = 0; i < gameObjects.size(); i++)
			{
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

		ImGui::End();
	}
}

void OutlinerScreen::ResetSelection()
{
	for (int i = 0; i < this->selection.size(); i++)
		this->selection[i] = false;
}
