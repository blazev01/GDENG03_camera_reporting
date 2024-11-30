#pragma once
#include "PhysicsSystem.h"
#include "RendererSystem.h"

class BaseComponentSystem
{
public:
	static void Initialize();
	static void Destroy();

	static PhysicsSystem* GetPhysicsSystem();
	static RendererSystem* GetRendererSystem();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&) {};
	BaseComponentSystem& operator=(BaseComponentSystem const&) {};

	static BaseComponentSystem* instance;

	PhysicsSystem* physicsSystem = nullptr;
	RendererSystem* rendererSystem = nullptr;
};

