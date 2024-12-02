#include "OutlinerScreen.h"
#include "../GameObjects/GameObjectManager.h"

#include <algorithm>


static const std::string PAYLOAD_GAMEOBJECT = "GAMEOBJECT";


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
		{
			this->selection.resize(gameObjects.size());
			std::fill(this->selection.begin(), this->selection.end(), false);
		}

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

			


			bool isSceneDropdown = ImGui::TreeNode("Scene Name");

			if (isSceneDropdown) {
				for (int i = 0; i < gameObjects.size(); i++) {
					// IGNORE OBJECTS WITH PARENTS. 
					// THEY WILL BE HANDLED RECURSIVELY

					if (gameObjects[i]->GetParent() == nullptr) {
						this->drawObjectTree(gameObjects[i], i);
					}
				}
			}

			if (isSceneDropdown)
				ImGui::TreePop();
			


			/*
			ImGui::PushID(1);
			bool is1 = ImGui::TreeNodeEx("1"); 
			{
				if (is1) {
					ImGui::PushID("1.1");
					bool is11 = ImGui::TreeNodeEx("1.1");
					
					if (is11) {
						ImGui::PushID("1.1.1");
						bool is111 = ImGui::TreeNodeEx("1.1.1");
						ImGui::PopID();

						if (is111)
							ImGui::TreePop();
					}
					
					ImGui::PopID();

					if (is11)
						ImGui::TreePop();


					ImGui::PushID("1.2");
					bool is12 = ImGui::TreeNodeEx("1.2");
					ImGui::PopID();

					if (is12)
						ImGui::TreePop();

				}

				
			}
			ImGui::PopID();

			if(is1)
				ImGui::TreePop();

			ImGui::PushID(2);
			bool is2 = ImGui::TreeNodeEx("2");
			ImGui::PopID();

			if (is2)
				ImGui::TreePop();*/
		}
	}
	ImGui::End();
}

void OutlinerScreen::drawObjectTree(GameObject* obj, int i)
{
	// TREE FOR SELF
	ImGui::PushID(obj->GetName().c_str());
	bool isOpen = ImGui::TreeNodeEx(obj->GetName().c_str(), ImGuiTreeNodeFlags_AllowItemOverlap);


	// CREATE TREES FOR CHILDREN
	if (isOpen) {
		for (int j = 0; j < obj->GetChildren().size(); j++) {
			ImGui::AlignTextToFramePadding();
			drawObjectTree(obj->GetChild(j), i * 100 + j);
		}
	}
	
	ImGui::PopID();
	// END OF TREE CONTENT
	




	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload(PAYLOAD_GAMEOBJECT.c_str(), obj, sizeof(GameObject));
		ImGui::Text(obj->GetName().c_str());

		ImGui::EndDragDropSource();
	}


	if (ImGui::BeginDragDropTarget()) {
		auto payload = ImGui::AcceptDragDropPayload(PAYLOAD_GAMEOBJECT.c_str());
		if (payload != nullptr) {
			GameObject* data = (GameObject*)payload->Data;


			GameObject* child = GameObjectManager::FindGameObject(data->GetName());

			if (child->GetParent() != nullptr) {
				child->GetParent()->DisownChild(child);
			}

			obj->AdoptChild(child);
		}

		ImGui::EndDragDropTarget();
	}

	
	// CLEAN TREE
	if (isOpen) {
		ImGui::TreePop();
	}
}