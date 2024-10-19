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
	//std::sort(first, last, ComparePriority);
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

void RenderQueue::Render(VertexShader* vertexShader, PixelShader* pixelShader)
{
	if (!instance->renderers.empty())
	{
		for (GameObject* renderer : instance->renderers)
			renderer->Draw(vertexShader, pixelShader);
	}
}

bool RenderQueue::ComparePriority(GameObject* a, GameObject* b)
{
	return a->GetPriority() < b->GetPriority();
}

RenderQueue::RenderQueue()
{

}

RenderQueue::~RenderQueue()
{

}
