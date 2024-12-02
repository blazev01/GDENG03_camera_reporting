#pragma once
#include "UIScreen.h"
#include "vector"
#include "unordered_map"

class GameObject;

class OutlinerScreen : public UIScreen
{
protected:
	OutlinerScreen();
	~OutlinerScreen();
	virtual void DrawUI() override;

	friend class UIManager;

private:
	//std::vector<bool> selection;

	std::unordered_map<std::string, bool> selectedTable;

	void drawObjectTree(GameObject* obj, int i);
};

