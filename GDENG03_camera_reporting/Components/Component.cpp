#include "Component.h"

Component::Component(std::string name, ComponentType type, GameObject* owner)
{
	this->name = name;
	this->type = type;
	this->owner = owner;
}

Component::~Component()
{

}

void Component::AttachOwner(GameObject* owner)
{
	this->owner = owner;
}

void Component::DetachOwner()
{
	this->owner = NULL;
	this->Destroy();
}

GameObject* Component::GetOwner()
{
	return this->owner;
}

Component::ComponentType Component::GetType()
{
	return this->type;
}

std::string Component::GetName()
{
	return this->name;
}
