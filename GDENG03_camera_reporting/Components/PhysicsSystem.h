#pragma once
#include "string"
#include "unordered_map"
#include "vector"
#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;

class PhysicsComponent;

class PhysicsSystem
{
public:
	typedef std::unordered_map<std::string, PhysicsComponent*> ComponentTable;
	typedef std::vector<PhysicsComponent*> ComponentList;

	PhysicsSystem();
	~PhysicsSystem();

	void RegisterComponent(PhysicsComponent* component);
	void UnregisterComponent(PhysicsComponent* component);
	void UnregisterByName(std::string name);
	PhysicsComponent* FindComponentByName(std::string name);
	ComponentList GetAllComponents();

	void UpdateAllComponents();
	PhysicsWorld* GetPhysicsWorld();
	PhysicsCommon* GetPhysicsCommon();

private:
	ComponentTable componentTable;
	ComponentList componentList;

	PhysicsWorld* physicsWorld;
	PhysicsCommon* physicsCommon;
};

