#pragma once
#include "UIScreen.h"
#include "vector"

class GameObject;

class OutlinerScreen : public UIScreen
{
protected:
	OutlinerScreen();
	~OutlinerScreen();
	virtual void DrawUI() override;

	friend class UIManager;

private:
	std::vector<bool> selection;

	void drawObjectTree(GameObject* obj, int i);
};

