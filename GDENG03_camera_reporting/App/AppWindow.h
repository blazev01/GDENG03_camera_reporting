#pragma once
#include "vector"
#include "../WindowSystem/Window.h"
#include "../InputSystem/InputListener.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnFocus() override;
	virtual void OnKillFocus() override;
	virtual void OnDestroy() override;

	virtual void OnKey(int key) override;
	virtual void OnKeyDown(int key) override;
	virtual void OnKeyUp(int key) override;

	virtual void OnMouseMove(const Vector2D& deltaMousePos) override;
	virtual void OnMouseButton(int button) override;
	virtual void OnMouseButtonDown(int button) override;
	virtual void OnMouseButtonUp(int button) override;

private:
	bool play = false;
};

