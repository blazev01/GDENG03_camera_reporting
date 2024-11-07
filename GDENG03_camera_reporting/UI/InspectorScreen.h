#pragma once
#include "UIScreen.h"

class Camera;

class InspectorScreen : public UIScreen
{
protected:
	InspectorScreen();
	~InspectorScreen();
	virtual void DrawUI() override;

	void CreateCameraControlsHeader(Camera* cam);

	friend class UIManager;
};