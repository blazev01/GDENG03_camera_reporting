#pragma once
#include "string"
#include "unordered_map"
#include "vector"

class Renderer;

class RendererSystem

{
public:
	typedef std::unordered_map<std::string, Renderer*> ComponentTable;
	typedef std::vector<Renderer*> ComponentList;

	RendererSystem();
	~RendererSystem();

	void RegisterComponent(Renderer* component);
	void UnregisterComponent(Renderer* component);
	void UnregisterByName(std::string name);
	Renderer* FindComponentByName(std::string name);
	std::vector<Renderer*> GetAllComponents();

	void UpdateAllComponents();

private:
	ComponentTable componentTable;
	ComponentList componentList;
};
