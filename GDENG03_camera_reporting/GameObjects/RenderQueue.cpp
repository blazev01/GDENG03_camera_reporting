#include "RenderQueue.h"

RenderQueue* RenderQueue::instance = NULL;

void RenderQueue::Initialize()
{
	instance = new RenderQueue();
}

void RenderQueue::AddRenderer(GameObject* renderer)
{
	instance->renderers.push_back(renderer);

	std::vector<GameObject*>::iterator first = instance->renderers.begin();
	std::vector<GameObject*>::iterator last = instance->renderers.end();

	auto compare = [](GameObject* a, GameObject* b)
		{
			return a->GetPriority() < b->GetPriority();
		};

	std::sort(first, last, compare);
}

void RenderQueue::RemoveRenderer(GameObject * renderer)
{
	if (instance->renderers.empty()) return;

	std::vector<GameObject*>::iterator it = instance->renderers.begin();

	while (it != instance->renderers.end() && *it != renderer) it++;

	if (*it == renderer)
	{
		(*it)->Release();
		instance->renderers.erase(it);
	}
}

void RenderQueue::Render(std::bitset<4> cullingMask)
{
	if (!instance->renderers.empty())
	{
		for (GameObject* renderer : instance->renderers)
			if (cullingMask[renderer->GetLayer()]) renderer->Draw();
	}
}

RenderQueue::RenderQueue()
{

}

RenderQueue::~RenderQueue()
{

}
