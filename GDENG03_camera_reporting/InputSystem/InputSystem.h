#pragma once
#include "map"
#include "unordered_set"
#include "InputListener.h"

class InputSystem
{
public:
	static void Initialize();
	static void Update();
	static void AddListener(InputListener* listener);
	static void RemoveListener(InputListener* listener);

private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator=(InputSystem const&) {};

	static InputSystem* instance;

	//std::map<InputListener*, InputListener*> listenerMap;
	std::unordered_set<InputListener*> listenerSet;
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};
};
