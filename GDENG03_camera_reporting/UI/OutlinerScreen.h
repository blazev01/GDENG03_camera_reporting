#pragma once
#include "UIScreen.h"
#include "vector"

class OutlinerScreen : public UIScreen
{
protected:
	OutlinerScreen();
	~OutlinerScreen();
	virtual void DrawUI() override;

	friend class UIManager;

private:
	void ResetSelection();

	std::vector<bool> selection;
};

