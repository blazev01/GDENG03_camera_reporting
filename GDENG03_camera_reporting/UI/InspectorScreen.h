#pragma once
#include "UIScreen.h"

class InspectorScreen : public UIScreen
{
protected:
	InspectorScreen();
	~InspectorScreen();
	virtual void DrawUI() override;

	friend class UIManager;
};

