#pragma once
#include "UIScreen.h"

class ProfilerScreen : public UIScreen
{
protected:
	ProfilerScreen();
	~ProfilerScreen();
	virtual void DrawUI() override;

	friend class UIManager;

private:
	float ticks = 0.0f;
	int frameCount = 0;
};

