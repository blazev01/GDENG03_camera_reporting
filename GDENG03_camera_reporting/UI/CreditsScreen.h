#pragma once
#include "UIScreen.h"
#include "../Resource/Texture.h"

class CreditsScreen : public UIScreen
{
protected:
	CreditsScreen();
	~CreditsScreen();

	virtual void DrawUI() override;

	friend class UIManager;

private:
	ImTextureID logo = NULL;
};

