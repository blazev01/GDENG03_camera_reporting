#pragma once
#include "GameObject.h"
#include "algorithm"
#include "bitset"

class RenderQueue
{
public:
	static void Initialize();
	static void AddRenderer(GameObject* renderer);
	static void RemoveRenderer(GameObject* renderer);
	static void Render(std::bitset<4> cullingMask);
	static std::vector<GameObject*> GetRenderers();
private:
	bool ComparePriority(GameObject* a, GameObject* b);

private:
	RenderQueue();
	~RenderQueue();
	RenderQueue(RenderQueue const&) {};
	RenderQueue& operator=(RenderQueue const&) {};

	static RenderQueue* instance;

	std::vector<GameObject*> renderers;
};

