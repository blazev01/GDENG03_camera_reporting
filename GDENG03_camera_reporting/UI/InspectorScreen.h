#pragma once
#include "UIScreen.h"
#include "../GameObjects/GameObject.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/Renderer.h"

class InspectorScreen : public UIScreen
{
protected:
	InspectorScreen();
	~InspectorScreen();
	virtual void DrawUI() override;

	friend class UIManager;

private:
	void ShowComponentList(GameObject* selected);
	void ShowTransform(GameObject* selected);
	void ShowRigidBody(PhysicsComponent* component);
	void ShowTexture(Renderer* component);
	void ShowDummyComponent();
	void ShowComponent();

	void ShowComponentsPopup(GameObject* selected);

	bool showTransform = true;
};

