#pragma once
#include "unordered_set"
#include "InputListener.h"
#include "../Math/Vector2.h"

class InputSystem
{
public:
	static void Initialize();
	static void Update();

	static void AddListener(InputListener* listener);
	static void RemoveListener(InputListener* listener);

	static Vector2 GetCursorPosition();
	static void SetCursorPosition(const float& x, const float& y);
	static void SetCursorPosition(const Vector2& position);
	static void ShowCursor(bool show);

	static bool IsKey(int key);
	static bool IsKeyDown(int key);
	static bool IsKeyUp(int key);

	static bool GetEnabled();
	static void SetEnabled(bool enabled);

private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator=(InputSystem const&) {};

	static InputSystem* instance;

	std::unordered_set<InputListener*> listenerSet;
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};

	Vector2 oldCursorPos;
	Vector2 cursorPos;
	bool enabled = true;
};
