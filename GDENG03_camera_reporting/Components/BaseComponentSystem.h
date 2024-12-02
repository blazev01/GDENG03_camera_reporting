#pragma once
#include "PhysicsSystem.h"
#include "RendererSystem.h"
#include "AnimationSystem.h"

class BaseComponentSystem
{
public:
	static void Initialize();
	static void Destroy();

	static PhysicsSystem* GetPhysicsSystem();
	static RendererSystem* GetRendererSystem();
	static AnimationSystem* GetAnimationSystem();

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&) {};
	BaseComponentSystem& operator=(BaseComponentSystem const&) {};

	static BaseComponentSystem* instance;

	PhysicsSystem* physicsSystem = nullptr;
	RendererSystem* rendererSystem = nullptr;
	AnimationSystem* animationSystem = nullptr;
};

