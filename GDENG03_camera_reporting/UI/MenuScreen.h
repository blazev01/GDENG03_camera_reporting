#pragma once
#include "UIScreen.h"
#include "UINames.h"
#include "CustomStyles.h"

class MenuScreen : public UIScreen
{
protected:
	MenuScreen();
	~MenuScreen();
	virtual void DrawUI() override;

	friend class UIManager;

private:
	void ShowMenuFile();
	void ShowMenuGameObject();
	void ShowMenuWindow();
	void ShowMenuAbout();
	void ShowMenuScreenCameras();

	void ShowMenuThemes();
	void ShowMenuCreateMesh();

	UINames uiNames;
	CustomStyles styles;
};

