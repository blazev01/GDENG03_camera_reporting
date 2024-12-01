#pragma once
#include "string"

class GameObject;

class Component
{
public:
	enum ComponentType
	{
		NotSet = -1,
		Script = 0,
		Renderer = 1,
		Input = 2,
		Physics = 3
	};

	Component(std::string name, ComponentType type, GameObject* owner);
	~Component();

	void AttachOwner(GameObject* owner);
	virtual void DetachOwner();

	GameObject* GetOwner();
	ComponentType GetType();
	std::string GetName();

	virtual void Perform(float deltaTime) = 0;
	virtual void Destroy() = 0;

protected:
	GameObject* owner;
	ComponentType type;
	std::string name;
};

