#pragma once
#include "UIScreen.h"
class CameraViewportScreen : public UIScreen
{
protected:
	CameraViewportScreen();
	~CameraViewportScreen();
	virtual void DrawUI() override;

	friend class UIManager;
};

