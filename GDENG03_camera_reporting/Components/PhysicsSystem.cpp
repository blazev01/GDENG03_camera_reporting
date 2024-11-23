#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "../EngineTime/EngineTime.h"

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
}

PhysicsSystem::~PhysicsSystem()
{
	this->physicsCommon->destroyPhysicsWorld(this->physicsWorld);
	delete this->physicsCommon;
}

void PhysicsSystem::RegisterComponent(PhysicsComponent* component)
{
	this->componentList.push_back(component);
	this->componentTable[component->GetName()] = component;
}

void PhysicsSystem::UnregisterComponent(PhysicsComponent* component)
{
	if (this->componentList.empty()) return;

	ComponentList::iterator it = this->componentList.begin();

	while (it != this->componentList.end() && *it != component) it++;

	if (*it == component)
	{
		this->componentTable.erase(component->GetName());
		this->componentList.erase(it);
	}
}

void PhysicsSystem::UnregisterByName(std::string name)
{
	if (this->componentList.empty()) return;

	ComponentList::iterator it = this->componentList.begin();

	while (it != this->componentList.end() && (*it)->GetName() != name) it++;

	if ((*it)->GetName() == name)
	{
		this->componentTable.erase((*it)->GetName());
		this->componentList.erase(it);
	}
}

PhysicsComponent* PhysicsSystem::FindComponentByName(std::string name)
{
	return this->componentTable[name];
}

std::vector<PhysicsComponent*> PhysicsSystem::GetAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::UpdateAllComponents()
{
	if (EngineTime::GetDeltaTime() > 0)
	{
		this->physicsWorld->update(EngineTime::GetDeltaTime());
		for (auto component : this->componentList)
			component->Perform(EngineTime::GetDeltaTime());
	}
}

PhysicsWorld* PhysicsSystem::GetPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::GetPhysicsCommon()
{
	return this->physicsCommon;
}
