#include "GameObjectManager.h"
#include "../EngineTime/EngineTime.h"

GameObjectManager* GameObjectManager::instance = NULL;

void GameObjectManager::Initialize()
{
	instance = new GameObjectManager();
}

void GameObjectManager::Update()
{
	if (!instance->gameObjects.empty())
	{
		for (GameObject* gameObject : instance->gameObjects)
			gameObject->Update(EngineTime::GetDeltaTime());
	}
}

void GameObjectManager::Draw(VertexShader* vertexShader, PixelShader* pixelShader)
{
	if (!instance->gameObjects.empty())
	{
		for (GameObject* gameObject : instance->gameObjects)
			gameObject->Draw(vertexShader, pixelShader);
	}
}

void GameObjectManager::Release()
{
	if (!instance->gameObjects.empty())
	{
		for (int i = instance->gameObjects.size() - 1; i >= 0; i--)
		{
			instance->gameObjects[i]->Release();
			instance->gameObjects.pop_back();
		}
	}
}

void GameObjectManager::AddGameObject(GameObject* gameObject)
{
	instance->gameObjects.push_back(gameObject);
}

void GameObjectManager::DeleteGameObject(GameObject* gameObject)
{
	if (instance->gameObjects.empty()) return;

	std::vector<GameObject*>::iterator it = instance->gameObjects.begin();

	while (it != instance->gameObjects.end() && *it != gameObject) it++;

	if (*it == gameObject)
	{
		(*it)->Release();
		instance->gameObjects.erase(it);
	}
}

void GameObjectManager::DeleteGameObject(std::string name)
{
	if (instance->gameObjects.empty()) return;

	std::vector<GameObject*>::iterator it = instance->gameObjects.begin();

	while (it != instance->gameObjects.end() && (*it)->GetName() != name) it++;

	if ((*it)->GetName() == name)
	{
		(*it)->Release();
		instance->gameObjects.erase(it);
	}
}

GameObject* GameObjectManager::Find(std::string name)
{
	if (instance->gameObjects.empty()) return NULL;

	std::vector<GameObject*>::iterator it = instance->gameObjects.begin();

	while (it != instance->gameObjects.end() && (*it)->GetName() != name) it++;

	if ((*it)->GetName() == name) return *it;

	return NULL;
}

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}
