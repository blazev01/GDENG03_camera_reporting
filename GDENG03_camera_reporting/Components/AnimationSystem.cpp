#include "AnimationSystem.h"
#include "AnimationComponent.h"
#include "../EngineTime/EngineTime.h"

AnimationSystem::AnimationSystem()
{
}

AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::RegisterComponent(AnimationComponent* component)
{
	this->componentList.push_back(component);
	this->componentTable[component->GetName()] = component;
}

void AnimationSystem::UnregisterComponent(AnimationComponent* component)
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

void AnimationSystem::UnregisterByName(std::string name)
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

AnimationComponent* AnimationSystem::FindComponentByName(std::string name)
{
	return this->componentTable[name];
}

std::vector<AnimationComponent*> AnimationSystem::GetAllComponents()
{
	return this->componentList;
}

void AnimationSystem::UpdateAllComponents()
{
	if (EngineTime::GetDeltaTime() > 0)
	{
		for (auto component : this->componentList)
			component->Perform(EngineTime::GetDeltaTime());
	}
}