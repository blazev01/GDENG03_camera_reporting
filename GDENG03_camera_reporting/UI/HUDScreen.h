#pragma once
#include "UIScreen.h"
#include "../Backend/Debug.h"
#include "../Math/Vector4D.h"
#include "../Resource/Texture.h"
#include "vector"
#include "string"

class HUDScreen : public UIScreen
{
private:
	enum HUDType {
		Text = 0,
		Button = 1,
		Image = 2
	};

	struct HUD {
		char name[64];
		bool enabled;

		HUDType type;
		ImVec2 position;
		ImVec2 scale;

		ImVec4 color;
		char text[128];

		Texture* tex;
		std::wstring path;
	};

public:
	HUDScreen();
	~HUDScreen();
	virtual void DrawUI() override;

	void DrawTextHUD(HUD& hud);
	void DrawButtonHUD(HUD& hud);
	void DrawImageHUD(HUD& hud);

	friend class UIManager;

private:
	std::vector<HUD> hudObjects;
	ImGuiChildFlags childFlags = ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY; 
};

