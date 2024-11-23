#pragma once
#include "UIScreen.h"
#include "../Backend/EditorAction.h"

class ActionsScreen : public UIScreen
{
protected:
	ActionsScreen();
	~ActionsScreen();
	virtual void DrawUI() override;

private:
	void SetGameObjectData(EditorAction* action);

	friend class UIManager;
};

