#include "InspectorScreen.h"
#include "../Resource/TextureManager.h"
#include "../GraphicsEngine/ShaderLibrary.h"
#include "../GameObjects/GameObjectManager.h"
#include "../Backend/ActionHistory.h"
#include "../Backend/Debug.h"
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
        else
        {
            const int maxLen = 21;
            char name[maxLen];

            if (selected.size() > 1)
            {
                strcpy_s(name, "Multiple Objects");

                ImGui::BeginDisabled(true);
                ImGui::InputText("Name", name, maxLen);
                ImGui::EndDisabled();
            }
            else
            {
                strcpy_s(name, selected[0]->GetName().c_str());

                if (ImGui::InputText("Name", name, maxLen) &&
                    ImGui::IsKeyPressed(ImGuiKey_Enter) &&
                    name[0] != '\0')
                    GameObjectManager::SetObjectName(selected[0]->GetName(), name);
            }

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

            this->ShowComponentList(selected);

            ImGui::NewLine();
            if (ImGui::Button("Add Component", ImVec2(ImGui::GetColumnWidth(), 20)))
            {
                ImGui::OpenPopup("Components");
            }

            this->ShowComponentsPopup(selected);
        }

        if (toDelete)
        {
            for (auto o : selected) GameObjectManager::DeleteGameObject(o);
            GameObjectManager::ClearSelection();
        }
    }
    ImGui::End();
}

void InspectorScreen::ShowComponentList(const std::vector<GameObject*>& selected)
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

    bool hasPhysics = true;
    bool hasRenderer = true;
    bool hasAnimation = true;
    std::vector<PhysicsComponent*> physics;
    std::vector<Renderer*> renderers;
    std::vector<AnimationComponent*> animations;

    for (auto gameObject : selected)
    {
        for (Component* component : gameObject->GetComponents())
        {
            switch (component->GetType())
            {
            case Component::Physics:
            {
                physics.push_back((PhysicsComponent*)component);
                break;
            }

            case Component::Renderer:
            {
                renderers.push_back((Renderer*)component);
                break;
            }

            case Component::Animation:
            {
                animations.push_back((AnimationComponent*)component);
                break;
            }

            default:
                break;
            }
        }
    }

    hasPhysics = physics.size() == selected.size();
    hasRenderer = renderers.size() == selected.size();
    hasAnimation = animations.size() == selected.size();



    if (hasPhysics)
    {
        if (ImGui::BeginChild("RigidBody", ImVec2(0, 0), childFlags))
        {
            if (ImGui::CollapsingHeader("RigidBody", ImGuiTreeNodeFlags_DefaultOpen))
            {
                this->ShowRigidBody(physics);
                if (ImGui::Button("Remove", ImVec2(ImGui::GetColumnWidth(), 0)))
                    for (auto p : physics) p->GetOwner()->DetachComponent(p);
            }
        }

        ImGui::EndChild();
    }
    if (hasRenderer)
    {
        if (ImGui::BeginChild("Renderer", ImVec2(0, 0), childFlags))
        {
            if (ImGui::CollapsingHeader("Renderer", ImGuiTreeNodeFlags_DefaultOpen))
            {
                this->ShowTexture(renderers);
                if (ImGui::Button("Remove", ImVec2(ImGui::GetColumnWidth(), 0)))
                    for (auto r : renderers) r->GetOwner()->DetachComponent(r);
            }
        }

        ImGui::EndChild();
    }

    if (hasAnimation)
    {
        if (ImGui::BeginChild("Animation", ImVec2(0, 0), childFlags))
        {
            if (ImGui::CollapsingHeader("Animation", ImGuiTreeNodeFlags_DefaultOpen))
            {
                this->ShowAnimation(animations);
                if (ImGui::Button("Remove", ImVec2(ImGui::GetColumnWidth(), 0)))
                    for (auto a : animations) a->GetOwner()->DetachComponent(a);
            }
        }

        ImGui::EndChild();
    }
}

void InspectorScreen::ShowTransform(const std::vector<GameObject*>&selected)
{
    Vector3D pos = selected[0]->GetLocalPosition();
    Vector3D rot = selected[0]->GetLocalRotation();
    Vector3D scale = selected[0]->GetLocalScale();
    bool isLocal = selected[0]->GetIsLocalTransform();
    bool recalculate = false;
    float width = 0.7f;

    float scenePos[3] = { pos.x, pos.y, pos.z };
    float sceneRot[3] = { rot.x * RAD2DEG, rot.y * RAD2DEG, rot.z * RAD2DEG };
    float sceneScale[3] = { scale.x, scale.y, scale.z };

    if (ImGui::Checkbox("Local Transform", &isLocal))
    {
        recalculate = true;
    }

    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::InputFloat3("Position", scenePos) &&
        ImGui::IsItemDeactivatedAfterEdit())
    {
        recalculate = true;
    }

    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::InputFloat3("Rotation", sceneRot) &&
        ImGui::IsItemDeactivatedAfterEdit())
    {
        sceneRot[0] *= DEG2RAD;
        sceneRot[1] *= DEG2RAD;
        sceneRot[2] *= DEG2RAD;

        recalculate = true;
    }

    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::InputFloat3("Scale", sceneScale) &&
        ImGui::IsItemDeactivatedAfterEdit())
    {
        recalculate = true;
    }
    
    if (recalculate)
    {
        for (auto gameObject : selected)
        {
            ActionHistory::RecordAction(gameObject);

            gameObject->SetIsLocalTransform(isLocal);
            gameObject->SetPosition(Vector3D(scenePos[0], scenePos[1], scenePos[2]));
            gameObject->SetRotation(Vector3D(sceneRot[0], sceneRot[1], sceneRot[2]));
            gameObject->SetScale(Vector3D(sceneScale[0], sceneScale[1], sceneScale[2]));

            gameObject->Recalculate();
        }
    }
}

void InspectorScreen::ShowRigidBody(const std::vector<PhysicsComponent*>& components)
{
    bool updateMass = false;
    bool updateType = false;
    bool updateGravity = false;

    float mass = components[0]->GetMass();
    int selectedItem = (int)components[0]->GetRigidBody()->getType();
    bool gravity = components[0]->GetRigidBody()->isGravityEnabled();

    float width = 0.7f;
    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::InputFloat("Mass", &mass) &&
        ImGui::IsItemDeactivatedAfterEdit())
    {
        updateMass = true;
    }

    static const char* items[]{ "Static","Kinematic","Dynamic" };
    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() * width);
    if (ImGui::Combo("Body Type", &selectedItem, items, IM_ARRAYSIZE(items)))
    {
        updateType = true;
    }

    if (ImGui::Checkbox("Gravity Enabled", &gravity))
    {
        updateGravity = true;
    }

    if (updateMass || updateType || updateGravity)
    {
        for (auto component : components)
        {
            if (updateMass) component->SetMass(mass);
            else if (updateType) component->GetRigidBody()->setType((BodyType)selectedItem);
            else if (updateGravity) component->GetRigidBody()->enableGravity(gravity);
        }
    }
}

void InspectorScreen::ShowTexture(const std::vector<Renderer*>& components)
{
    bool updateTexture = false;

    std::wstring selectedFile = components[0]->GetTextureFilePath();
    if (selectedFile.empty()) selectedFile = L"..\\Assets\\Textures\\DLSU-LOGO.png";
    Texture* currentTexture = components[0]->GetTexture();

    for (auto component : components)
    {
        if (currentTexture)
        {
            std::wstring relativeCurrentTextureFile = L"..\\Assets\\Textures\\" + std::filesystem::path(currentTexture->GetFilePath()).filename().wstring();

            if (relativeCurrentTextureFile != selectedFile)
            {
                Debug::Log("No Texture currently exists for " + component->GetOwner()->GetName() + ". Creating Texture...");

                currentTexture = TextureManager::CreateTextureFromFile(selectedFile.c_str());
                component->SetTexture(currentTexture);
                component->SetTextureFilePath(selectedFile);
            }
        }
        else
        {
            Debug::Log("No Texture currently exists for " + component->GetOwner()->GetName() + ". Creating Texture...");

            currentTexture = TextureManager::CreateTextureFromFile(selectedFile.c_str());
            component->SetTexture(currentTexture);
            component->SetTextureFilePath(selectedFile);
        }

    }

    ImGui::Image((ImTextureID)currentTexture->GetSRV(), ImVec2(50, 50));

    ImGui::SameLine();
    ImGui::BeginGroup();

    std::string fileName = std::filesystem::path(selectedFile).filename().string();
    ImGui::Text(fileName.c_str());

    if (ImGui::Button("Change Texture"))
        ImGui::OpenPopup("Select Texture");
    ImGui::EndGroup();

    if (ImGui::BeginPopup("Select Texture"))
    {
        ImGui::Text("Textures");
        ImGui::Separator();

        ImGui::BeginChild("TextureList", ImVec2(200, 300), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        for (const auto& entry : std::filesystem::directory_iterator("..\\Assets\\Textures"))
        {
            if (entry.is_regular_file())
            {
                std::wstring filename = entry.path().wstring();
                std::wstring displayName = std::filesystem::path(filename).filename().wstring();

                Texture* previewTexture = TextureManager::CreateTextureFromFile(filename.c_str());
                if (previewTexture)
                {
                    ImGui::Image((ImTextureID)previewTexture->GetSRV(), ImVec2(15, 15));
                    ImGui::SameLine();
                }

                if (ImGui::Selectable(std::string(displayName.begin(), displayName.end()).c_str(), filename == selectedFile))
                {
                    selectedFile = filename;
                    updateTexture = true;
                }
            }
        }

        if (updateTexture)
        {
            for (auto component : components)
            {
                component->SetTextureFilePath(selectedFile);
                component->SetTexture(currentTexture);
            }
        }

        ImGui::EndChild();
        ImGui::EndPopup();
    }
}

void InspectorScreen::ShowAnimation(std::vector<AnimationComponent*>& components)
{
    if (ImGui::Button("Log Keyframe")) {
        for (auto it : components) {
            it->AddKeyframe();
        }
    }

    for (auto comp : components) {
        if (ImGui::TreeNode(comp->GetOwner()->GetName().c_str())) {
            
            // LOOP ANIMATION?
            bool isLoop = comp->GetIsLoop();
            if (ImGui::Checkbox("Loop", &isLoop)) {
                comp->SetLoop(isLoop);
            }


            // KEYFRAMES LIST
            for (float t : comp->GetTimeStamps()) {
                std::stringstream s;
                s << t;
                ImGui::PushID(s.str().c_str());

                // ADJUST KEYFRAME
                float modT = t;
                if (ImGui::InputFloat("Time", &modT)) {
                    if (modT < 0.f)
                        modT = 0.f;
                    
                    if (t != modT)
                        comp->UpdateTimeStamp(t, modT);
                }
                
                // REMOVE KEYFRAME
                if (ImGui::Button("Delete")) {
                    comp->RemoveKeyframe(t);
                }

                // KEYFRAME OF TRANSFORMS
                //ImGui::DragFloat3("P", )


                ImGui::PopID();
            }

            ImGui::TreePop();
        }
    }
}

void InspectorScreen::ShowComponentsPopup(const std::vector<GameObject*>& selected)
{
    if (ImGui::BeginPopup("Components", ImGuiWindowFlags_NoDocking))
    {
        Component::ComponentType type = Component::NotSet;
        if (ImGui::Button("Physics Component", ImVec2(ImGui::GetColumnWidth(), 0)))
        {
            type = Component::Physics;
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Texture Component", ImVec2(ImGui::GetColumnWidth(), 0)))
        {
            type = Component::Renderer;
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Animation Component", ImVec2(ImGui::GetColumnWidth(), 0)))
        {
            type = Component::Animation;
            ImGui::CloseCurrentPopup();
        }


        for (auto gameObject : selected)
        {
            switch (type)
            {
            case Component::Script:
            {
                break;
            }
            case Component::Renderer:
            {
                if (!gameObject->GetComponentOfType(Component::Renderer, "Renderer"))
                {
                    PixelShader* pixelShader = ShaderLibrary::GetPixelShader(L"TexturePixelShader.hlsl");
                    VertexShader* vertexShader = ShaderLibrary::GetVertexShader(L"VertexShader.hlsl");
                    Renderer* component = new Renderer("Renderer", gameObject, vertexShader, pixelShader);
                    gameObject->SetPixelShader(pixelShader);
                    gameObject->AttachComponent(component);
                }
                break;
            }
            case Component::Input:
            {
                break;
            }
            case Component::Physics:
            {
                if (!gameObject->GetComponentOfType(Component::Physics, "RigidBody"))
                {
                    PhysicsComponent* component = new PhysicsComponent("RigidBody", gameObject);
                    gameObject->AttachComponent(component);
                }
                break;
            }

            case Component::Animation: {
                if (!gameObject->GetComponentOfType(Component::Animation, "Animation"))
                {
                    AnimationComponent* component = new AnimationComponent("Animation", gameObject);
                    gameObject->AttachComponent(component);
                }
                ImGui::CloseCurrentPopup();
                break;
            }




            default:
                break;
            }
        }

        ImGui::EndPopup();
    }
}
