#pragma once
#include "string"
#include "unordered_map"
#include "vector"


class AnimationComponent;

class AnimationSystem
{
public:
	typedef std::unordered_map<std::string, AnimationComponent*> ComponentTable;
	typedef std::vector<AnimationComponent*> ComponentList;

	AnimationSystem();
	~AnimationSystem();

	void RegisterComponent(AnimationComponent* component);
	void UnregisterComponent(AnimationComponent* component);
	void UnregisterByName(std::string name);
	AnimationComponent* FindComponentByName(std::string name);
	ComponentList GetAllComponents();

	void UpdateAllComponents();

private:
	ComponentTable componentTable;
	ComponentList componentList;
};