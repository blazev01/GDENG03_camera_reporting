#pragma once
#include "UIScreen.h"
class ScenePlayOptionsScreen : public UIScreen
{
protected:
	ScenePlayOptionsScreen();
	~ScenePlayOptionsScreen();
	virtual void DrawUI() override;

	friend class UIManager;
};

