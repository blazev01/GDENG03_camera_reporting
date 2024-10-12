#pragma once

class InputListener
{
public:
	InputListener() {}
	~InputListener() {}

	virtual void OnKey(int key) = 0;
	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;
};

