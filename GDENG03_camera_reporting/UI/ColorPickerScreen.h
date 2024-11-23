#pragma once
#include "UIScreen.h"

class ColorPickerScreen : public UIScreen
{
protected:
	ColorPickerScreen();
	~ColorPickerScreen();
	virtual void DrawUI() override;

	friend class UIManager;

private:
	ImTextureID color = NULL;
};

