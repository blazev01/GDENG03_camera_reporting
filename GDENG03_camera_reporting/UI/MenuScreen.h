#pragma once
#include "UIScreen.h"

class MenuScreen : public UIScreen
{
protected:
	MenuScreen();
	~MenuScreen();
	virtual void DrawUI() override;

	friend class UIManager;
};

