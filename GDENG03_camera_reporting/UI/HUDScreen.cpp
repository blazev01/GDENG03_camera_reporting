#include "HUDScreen.h"
#include "../Resource/TextureManager.h"

#include "filesystem"
#include <string>
#include <sstream>

HUDScreen::HUDScreen() : UIScreen("HUD_SCREEN")
{
}

HUDScreen::~HUDScreen()
{
}

void HUDScreen::DrawUI()
{
    ImGui::Begin("UI Inspector", &this->enabled, ImGuiWindowFlags_NoCollapse); 
    
    if (ImGui::Button("Add Button")) {
        HUD button;
        strcpy_s(button.name, "Button");
        button.enabled = true;
        button.type = HUDType::Button;
        button.position = ImVec2(0.0f, 0.0f);
        button.scale = ImVec2(120.0f, 50.0f);
        button.color = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
        strcpy_s(button.text, "Button");
        button.tex = nullptr;

        this->hudObjects.push_back(button);
    }

    ImGui::SameLine();
    if (ImGui::Button("Add Text")) {
        HUD text;
        strcpy_s(text.name, "Button");
        text.enabled = true;
        text.type = HUDType::Text;
        text.position = ImVec2(0.0f, 0.0f);
        text.scale = ImVec2(120.0f, 50.0f);
        text.color = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
        strcpy_s(text.text, "text");

        this->hudObjects.push_back(text);
    }

    ImGui::SameLine();
    if (ImGui::Button("Add Image")) {
        HUD img;
        strcpy_s(img.name, "Image");
        img.enabled = true;
        img.type = HUDType::Image;
        img.position = ImVec2(0.0f, 0.0f);
        img.scale = ImVec2(120.0f, 50.0f);

        img.tex = TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\DLSU-LOGO.png");
        img.path = L"..\\Assets\\Textures\\DLSU-LOGO.png";

        this->hudObjects.push_back(img);
    }

    for (auto& hud : this->hudObjects) {
        switch (hud.type) 
        {
        case HUDType::Button: 
        {
            this->DrawButtonHUD(hud);
            break;
        }

        case HUDType::Image:
        {
            this->DrawImageHUD(hud);
            break;
        }

        case HUDType::Text:
        {
            this->DrawTextHUD(hud);
            break;
        }

        default:
            break;
        }
    }

    ImGui::End();


}

void HUDScreen::DrawTextHUD(HUD& hud)
{
    
}

void HUDScreen::DrawButtonHUD(HUD& hud)
{
    char name[64];
    bool enabled = hud.enabled;

    HUDType type = hud.type;
    ImVec2 position = hud.position;
    ImVec2 scale = hud.scale;

    ImVec4 color = hud.color;
    char text[128];

    strcpy_s(name, hud.name);
    strcpy_s(text, hud.text);

    std::stringstream ss;
    ss << &hud;
    std::string uniqueName = name + ss.str();

    ImGui::BeginChild(uniqueName.c_str(), ImVec2(0, 0), childFlags);
        ImGui::InputText(("Name##" + uniqueName).c_str(), name, IM_ARRAYSIZE(name));
        ImGui::Separator();

        ImGui::Text("Position");
        ImGui::InputFloat2(("Position##" + uniqueName).c_str(), (float*)&position);

        ImGui::Text("Scale");
        ImGui::InputFloat2(("Scale##" + uniqueName).c_str(), (float*)&scale);

        ImGui::Text("Color");
        ImGui::ColorEdit4(("Color##" + uniqueName).c_str(), (float*)&color);

        ImGui::Text("Button Text");
        ImGui::InputText(("Text##" + uniqueName).c_str(), text, IM_ARRAYSIZE(text));
        ImGui::EndChild();
    
    ImGui::Separator();

    ImGui::SetNextWindowSize(scale);
    ImGui::SetNextWindowPos(position, ImGuiCond_Always);
    ImGui::Begin(uniqueName.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings);
    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetColorU32(color));

    const char* displayedText = text[0] == '\0' ? " " : text;

    if (ImGui::Button(displayedText, scale))
    {
        // Button action here
    }
    ImGui::PopStyleColor();

    ImGui::End();

    strcpy_s(hud.name, name);
    hud.position = position;
    hud.scale = scale;
    hud.color = color;
    strcpy_s(hud.text, text);
}


void HUDScreen::DrawImageHUD(HUD& hud)
{
    char name[64];
    bool enabled = hud.enabled;

    HUDType type = hud.type;
    ImVec2 position = hud.position;
    ImVec2 scale = hud.scale;

    strcpy_s(name, hud.name);
    Texture* tex = hud.tex;
    std::wstring path = hud.path;

    std::stringstream ss;
    ss << &hud;
    std::string uniqueName = name + ss.str();

    ImGui::BeginChild(uniqueName.c_str(), ImVec2(0, 0), childFlags);
    ImGui::InputText(("Name##" + uniqueName).c_str(), name, IM_ARRAYSIZE(name));
    ImGui::Separator();

    ImGui::Text("Position");
    ImGui::InputFloat2(("Position##" + uniqueName).c_str(), (float*)&position);

    ImGui::Text("Scale");
    ImGui::InputFloat2(("Scale##" + uniqueName).c_str(), (float*)&scale);

    ImGui::Text("Texture");
    ImGui::Image((ImTextureID)tex->GetSRV(), ImVec2(50, 50));

    ImGui::SameLine();
    ImGui::BeginGroup();

    std::string fileName = std::filesystem::path(path).filename().string();
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

                if (ImGui::Selectable(std::string(displayName.begin(), displayName.end()).c_str(), filename == path)) 
                {
                    path = filename;
                    tex = TextureManager::CreateTextureFromFile(path.c_str());
                }
            }
        }

        ImGui::EndChild();
        ImGui::EndPopup();
    }

    ImGui::EndChild();

    ImGui::Separator();

    ImGui::SetNextWindowSize(scale);
    ImGui::SetNextWindowPos(position, ImGuiCond_Always);
    ImGui::Begin(uniqueName.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings);
    ImGui::Image((ImTextureID)tex->GetSRV(), scale);
    ImGui::End();

    // Save changes back to the original hud object
    strcpy_s(hud.name, name);
    hud.position = position;
    hud.scale = scale;
    hud.tex = tex;
}

