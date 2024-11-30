#include "RendererSystem.h"
#include "Renderer.h"
#include "../EngineTime/EngineTime.h"

RendererSystem::RendererSystem()
{
}

RendererSystem::~RendererSystem()
{
}

void RendererSystem::RegisterComponent(Renderer* component)
{
    this->componentList.push_back(component);
    this->componentTable[component->GetName()] = component;
}

void RendererSystem::UnregisterComponent(Renderer* component)
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

void RendererSystem::UnregisterByName(std::string name)
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

Renderer* RendererSystem::FindComponentByName(std::string name)
{
	return this->componentTable[name];
}

std::vector<Renderer*> RendererSystem::GetAllComponents()
{
	return this->componentList;
}

void RendererSystem::UpdateAllComponents()
{
	for (auto component : this->componentList)
		component->Perform(EngineTime::GetDeltaTime());
}
