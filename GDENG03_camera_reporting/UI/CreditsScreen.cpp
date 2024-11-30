#include "CreditsScreen.h"
#include "../GraphicsEngine/GraphicsEngine.h"

CreditsScreen::CreditsScreen() : UIScreen("CREDITS_SCREEN")
{
	this->enabled = false;
	Texture* logo = TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\DLSU-LOGO.png");
	if (logo && logo->GetSRV()) this->logo = (ImTextureID)logo->GetSRV();
}

CreditsScreen::~CreditsScreen()
{

}

void CreditsScreen::DrawUI()
{
	if (ImGui::Begin("Credits", &this->enabled))
	{

		if (this->logo) ImGui::Image(this->logo, ImVec2(250, 250));
		ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "About");
		ImGui::Text("Scene Editor v0.02");
		ImGui::Text("Developed by: Vaughn Vincent M. Cordero");
		ImGui::Text("");
		ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "Acknowledgements:");
		ImGui::Text("PardCode Game Engine Tutorial");
		ImGui::Text("Doc Neil's GDENG03 Course");
	}
	ImGui::End();
}
