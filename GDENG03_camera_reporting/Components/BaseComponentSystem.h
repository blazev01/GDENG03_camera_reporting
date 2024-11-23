#pragma once
#include "PhysicsSystem.h"

class BaseComponentSystem
{
public:
	static void Initialize();
	static void Destroy();

	static PhysicsSystem* GetPhysicsSystem();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&) {};
	BaseComponentSystem& operator=(BaseComponentSystem const&) {};

	static BaseComponentSystem* instance;

	PhysicsSystem* physicsSystem = nullptr;
};

