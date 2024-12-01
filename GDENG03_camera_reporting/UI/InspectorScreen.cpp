#include "InspectorScreen.h"
#include "../Resource/TextureManager.h"
#include "../GraphicsEngine/ShaderLibrary.h"
#include "../GameObjects/GameObjectManager.h"
#include "../Backend/ActionHistory.h"
#include "../EngineTime/EngineTime.h"

#include "filesystem"

#define RAD2DEG 57.2958
#define DEG2RAD 0.0174533

InspectorScreen::InspectorScreen() : UIScreen("INSPECTOR_SCREEN")
{

}

InspectorScreen::~InspectorScreen()
{

}

void InspectorScreen::DrawUI()
{
	if (ImGui::Begin("Inspector", &this->enabled, ImGuiWindowFlags_NoCollapse))
    {
        std::vector<GameObject*> selected = GameObjectManager::GetSelectedObjects();
        bool toDelete = false;

        if (selected.empty())
        {
            ImGui::Text("No game object selected.");
        }
        else if (selected.size() == 1)
        {
            const int maxLen = 21;
            char name[maxLen];
            strcpy_s(name, selected[0]->GetName().c_str());

            if (ImGui::InputText("Name", name, maxLen) &&
                ImGui::IsKeyPressed(ImGuiKey_Enter) &&
                name[0] != '\0')
                GameObjectManager::SetObjectName(selected[0]->GetName(), name);

            if (ImGui::BeginTable("EnableDelete", 3))
            {
                ImGui::TableNextColumn();
                bool enabled = selected[0]->GetEnabled();
                ImGui::Checkbox("Enabled", &enabled);
                selected[0]->SetEnabled(enabled);

                ImGui::TableSetColumnIndex(2);
                toDelete = ImGui::Button("Delete", ImVec2(ImGui::GetColumnWidth(2), 0));
                ImGui::EndTable();
            }

            this->ShowComponentList(selected[0]);

            ImGui::NewLine();
            if (ImGui::Button("Add Component", ImVec2(ImGui::GetColumnWidth(), 20)))
            {
                ImGui::OpenPopup("Components");
            }

            this->ShowComponentsPopup(selected[0]);
        }
        else
        {
            const int maxLen = 21;
            char name[maxLen] = "Multiple Objects";

            ImGui::BeginDisabled(true);
            ImGui::InputText("Name", name, maxLen);
            ImGui::EndDisabled();

            if (ImGui::BeginTable("EnableDelete", 3))
            {
                ImGui::TableNextColumn();
                bool enabled = selected[0]->GetEnabled();
                ImGui::Checkbox("Enabled", &enabled);
                for (auto o : selected) o->SetEnabled(enabled);

                ImGui::TableSetColumnIndex(2);
                toDelete = ImGui::Button("Delete", ImVec2(ImGui::GetColumnWidth(2), 0));
                ImGui::EndTable();
            }

            ImGui::NewLine();
            if (ImGui::Button("Add Component", ImVec2(ImGui::GetColumnWidth(), 20)))
            {
                ImGui::OpenPopup("Components");
            }
        }

        if (toDelete)
        {
            for (auto o : selected) GameObjectManager::DeleteGameObject(o);
            GameObjectManager::ClearSelection();
        }
    }
    ImGui::End();
}

void InspectorScreen::ShowComponentList(GameObject* selected)
{
    ImGuiChildFlags childFlags =
        ImGuiChildFlags_Borders |
        ImGuiChildFlags_AutoResizeY;

    if (ImGui::BeginChild("Transform", ImVec2(0, 0), childFlags))
    {
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            this->ShowTransform(selected);

        ImGui::EndChild();
    }

    for (Component* component : selected->GetComponents())
    {
        const int maxLen = 21;
        char compName[maxLen];
        strcpy_s(compName, component->GetName().c_str());
        if (ImGui::BeginChild(compName, ImVec2(0, 0), childFlags))
        {
            if (ImGui::CollapsingHeader(compName, ImGuiTreeNodeFlags_DefaultOpen))
            {
                switch (component->GetType())
                {
                case Component::Physics:
                {
                    this->ShowRigidBody((PhysicsComponent*)component);
                    break;
                }
                
                case Component::Renderer:
                {
                    this->ShowTexture((Renderer*) component);
                    break;
                }

                default:
                    this->ShowComponent();
                    break;
                }

                if (ImGui::Button("Remove", ImVec2(ImGui::GetColumnWidth(), 0)))
                {
                    selected->DetachComponent(component);
                }
            }

            ImGui::EndChild();
        }
    }

    //if (ImGui::BeginChild("Dummy Component", ImVec2(0, 0), childFlags))
    //{
    //    if (ImGui::CollapsingHeader("Rick Roll Component", ImGuiTreeNodeFlags_DefaultOpen))
    //        this->ShowDummyComponent();
    //    ImGui::EndChild();
    //}
}

void InspectorScreen::ShowTransform(GameObject* selected)
{
    Vector3D pos = selected->GetLocalPosition();
    Vector3D rot = selected->GetLocalRotation();
    Vector3D scale = selected->GetLocalScale();

    float scenePos[3] = { pos.x, pos.y, pos.z };
    float sceneRot[3] = { rot.x * RAD2DEG, rot.y * RAD2DEG, rot.z * RAD2DEG };
    float sceneScale[3] = { scale.x, scale.y, scale.z };

    float width = 0.7f;
    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::InputFloat3("Position", scenePos) &&
        ImGui::IsItemDeactivatedAfterEdit())
    {
        ActionHistory::RecordAction(selected);
        selected->SetPosition(Vector3D(scenePos[0], scenePos[1], scenePos[2]));
        selected->Recalculate();
    }

    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::InputFloat3("Rotation", sceneRot) &&
        ImGui::IsItemDeactivatedAfterEdit())
    {
        sceneRot[0] *= DEG2RAD;
        sceneRot[1] *= DEG2RAD;
        sceneRot[2] *= DEG2RAD;

        ActionHistory::RecordAction(selected);
        selected->SetRotation(Vector3D(sceneRot[0], sceneRot[1], sceneRot[2]));
        selected->Recalculate();
    }

    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::InputFloat3("Scale", sceneScale) &&
        ImGui::IsItemDeactivatedAfterEdit())
    {
        ActionHistory::RecordAction(selected);
        selected->SetScale(Vector3D(sceneScale[0], sceneScale[1], sceneScale[2]));
        selected->Recalculate();
    }
}

void InspectorScreen::ShowRigidBody(PhysicsComponent* component)
{
    float mass = component->GetMass();
    float width = 0.7f;
    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::InputFloat("Mass", &mass) &&
        ImGui::IsItemDeactivatedAfterEdit())
        component->SetMass(mass);

    static const char* items[]{ "Static","Kinematic","Dynamic" };
    int selectedItem = (int)component->GetRigidBody()->getType();
    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::Combo("Body Type", &selectedItem, items, IM_ARRAYSIZE(items)))
    {
        component->GetRigidBody()->setType((BodyType)selectedItem);
    }

    bool gravity = component->GetRigidBody()->isGravityEnabled();
    if (ImGui::Checkbox("Gravity Enabled", &gravity))
    {
        component->GetRigidBody()->enableGravity(gravity);
    }
}

void InspectorScreen::ShowTexture(Renderer* component)
{
    std::wstring selectedFile = component->GetTextureFilePath();
    if (selectedFile.empty()) selectedFile = L"DLSU-LOGO.png";

    Texture* currentTexture = component->GetTexture();

    if (!currentTexture || currentTexture->GetFilePath() != selectedFile)
    {
        std::wstring fullPath = L"..\\Assets\\Textures\\" + selectedFile;
        currentTexture = TextureManager::CreateTextureFromFile(fullPath.c_str());
        component->SetTexture(currentTexture);
    }

    ImGui::Image((ImTextureID)currentTexture->GetSRV(), ImVec2(50, 50));

    ImGui::SameLine(); 
    ImGui::BeginGroup(); 
        ImGui::Text(std::string(selectedFile.begin(), selectedFile.end()).c_str());

        if (ImGui::Button("Change Texture"))
            ImGui::OpenPopup("Select Texture");
    ImGui::EndGroup(); 

    if (ImGui::BeginPopup("Select Texture"))
    {
        for (const auto& entry : std::filesystem::directory_iterator("..\\Assets\\Textures"))
        {
            if (entry.is_regular_file())
            {
                std::wstring filename = entry.path().filename().wstring();

                if (ImGui::Selectable(std::string(filename.begin(), filename.end()).c_str(), filename == selectedFile))
                {
                    selectedFile = filename;
                    component->SetTextureFilePath(selectedFile);
                    component->SetTexture(currentTexture);
                }
            }
        }
        ImGui::EndPopup();
    }
}


void InspectorScreen::ShowDummyComponent()
{
    ImGui::Text("Never gonna give you up");
    ImGui::Text("Never gonna let you down");
    ImGui::Text("Never gonna run around and desert you");
    ImGui::Text("Never gonna make you cry");
    ImGui::Text("Never gonna say goodbye");
    ImGui::Text("Never gonna tell a lie and hurt you");
}

void InspectorScreen::ShowComponent()
{
    ImGui::Text("Insert serialized fields\n\n\n\n\n");
}

void InspectorScreen::ShowComponentsPopup(GameObject* selected)
{
    if (ImGui::BeginPopup("Components", ImGuiWindowFlags_NoDocking))
    {
        if (ImGui::Button("Physics Component", ImVec2(ImGui::GetColumnWidth(), 0)))
        {
            if (!selected->GetComponentOfType(Component::Physics, "RigidBody"))
            {
                PhysicsComponent* component = new PhysicsComponent("RigidBody", selected);
                selected->AttachComponent(component);
            }
            
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Texture Component", ImVec2(ImGui::GetColumnWidth(), 0))) 
        {
            if (!selected->GetComponentOfType(Component::Renderer, "Renderer")) 
            {
                PixelShader* pixelShader = ShaderLibrary::GetPixelShader(L"TexturePixelShader.hlsl");
                Renderer* component = new Renderer("Renderer", selected, selected->GetVertexShader(), pixelShader);
                selected->SetPixelShader(pixelShader);
                selected->AttachComponent(component);
            }

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}
