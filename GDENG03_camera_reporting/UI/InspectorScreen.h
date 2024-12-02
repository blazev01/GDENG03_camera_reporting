#pragma once
#include "UIScreen.h"
#include "../GameObjects/GameObject.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/Renderer.h"

class InspectorScreen : public UIScreen
{
protected:
	InspectorScreen();
	~InspectorScreen();
	virtual void DrawUI() override;

	friend class UIManager;

private:
	void ShowComponentList(const std::vector<GameObject*>& selected);
	void ShowTransform(const std::vector<GameObject*>& selected);
	void ShowRigidBody(const std::vector<PhysicsComponent*>& components);
	void ShowTexture(const std::vector<Renderer*>& components);
	void ShowAnimation(std::vector<AnimationComponent*>& components);
	void ShowComponentsPopup(const std::vector<GameObject*>& selected);
	
	bool showTransform = true;
};

