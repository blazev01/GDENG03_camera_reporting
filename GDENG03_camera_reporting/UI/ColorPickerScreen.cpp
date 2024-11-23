#include "ColorPickerScreen.h"
#include "../GraphicsEngine/GraphicsEngine.h"

ColorPickerScreen::ColorPickerScreen() : UIScreen("COLOR_PICKER_SCREEN")
{
	this->enabled = false;
	Texture* color = TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\color-triangle.png");
	if (color && color->GetSRV()) this->color = (ImTextureID)color->GetSRV();
}

ColorPickerScreen::~ColorPickerScreen()
{

}

void ColorPickerScreen::DrawUI()
{
	if (ImGui::Begin("Color Picker", &this->enabled))
	{
		ImGui::Image(this->color, ImVec2(250, 250));

		ImGui::End();
	}
}
