#pragma once
#include "../Math/Vector2D.h"

class InputListener
{
public:
	InputListener() {}
	~InputListener() {}

	virtual void OnKey(int key) = 0;
	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;

	virtual void OnMouseMove(const Vector2D& deltaMousePos) = 0;
	virtual void OnMouseButton(int button) = 0;
	virtual void OnMouseButtonDown(int button) = 0;
	virtual void OnMouseButtonUp(int button) = 0;
};

