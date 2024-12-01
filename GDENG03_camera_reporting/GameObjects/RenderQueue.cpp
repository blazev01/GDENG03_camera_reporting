#include "RenderQueue.h"

RenderQueue* RenderQueue::instance = NULL;

void RenderQueue::Initialize()
{
	instance = new RenderQueue();
}

void RenderQueue::Destroy()
{
	delete instance;
}

void RenderQueue::AddRenderer(GameObject* renderer)
{
	instance->renderers.push_back(renderer);
	instance->SortByPriority();
}

void RenderQueue::RemoveRenderer(GameObject * renderer)
{
	if (instance->renderers.empty()) return;

	std::vector<GameObject*>::iterator it = instance->renderers.begin();

	while (it != instance->renderers.end() && *it != renderer) it++;

	if (*it == renderer) instance->renderers.erase(it);
}

void RenderQueue::RemoveAllRenderers()
{
	instance->renderers.clear();
}

void RenderQueue::SortByPriority()
{
	std::vector<GameObject*>::iterator first = instance->renderers.begin();
	std::vector<GameObject*>::iterator last = instance->renderers.end();

	auto compare = [](GameObject* a, GameObject* b)
		{
			return a->GetPriority() < b->GetPriority();
		};

	std::sort(first, last, compare);
}

void RenderQueue::Render(std::bitset<4> cullingMask, Matrix4x4 view, Matrix4x4 proj)
{
	if (!instance->renderers.empty())
	{
		for (GameObject* renderer : instance->renderers)
			if (renderer->GetEnabled() &&
				cullingMask[renderer->GetLayer()])
				renderer->Draw(view, proj);
	}
}

RenderQueue::RenderQueue()
{

}

RenderQueue::~RenderQueue()
{

}
