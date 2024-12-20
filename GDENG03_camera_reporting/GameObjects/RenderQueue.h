#pragma once
#include "GameObject.h"
#include "algorithm"
#include "bitset"

class RenderQueue
{
public:
	static void Initialize();
	static void Destroy();

	static void AddRenderer(GameObject* renderer);
	static void RemoveRenderer(GameObject* renderer);
	static void RemoveAllRenderers();

	static void SortByPriority();
	static void Render(std::bitset<4> cullingMask, Matrix4x4 view, Matrix4x4 proj);

private:
	RenderQueue();
	~RenderQueue();
	RenderQueue(RenderQueue const&) {};
	RenderQueue& operator=(RenderQueue const&) {};

	static RenderQueue* instance;

	std::vector<GameObject*> renderers;
	std::vector<GameObject*> gizmos;
};

